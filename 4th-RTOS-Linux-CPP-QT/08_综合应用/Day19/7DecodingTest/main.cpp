extern "C"
{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
}

FILE * outVideoFp = nullptr, * outAudioFp = nullptr;

static uint8_t *video_dst_data[4] = {NULL};
static int      video_dst_linesize[4];
static int video_dst_bufsize;
static int video_frame_count = 0;
static int audio_frame_count = 0;

AVPixelFormat pix_fmt;

static int openCodecContext(int *stream_idx,
                              AVCodecContext **dec_ctx,
                              AVFormatContext *fmt_ctx,
                              enum AVMediaType type);
static int decodePacket(AVCodecContext *dec, const AVPacket *pkt);
static int outputVideoFrame(AVFrame *frame);
static int outputAudioFrame(AVFrame *frame);
static int get_format_from_sample_fmt(const char **fmt,
                                      enum AVSampleFormat sample_fmt);

int main()
{
    int ret = 0;

    const char * srcFilename = "D:\\videos\\lldq-tkdt.mp4";
    const char * videoDstFilename = "lldq.yuv";
    const char * audioDstFilename = "lldq.pcm";

    outVideoFp = fopen(videoDstFilename, "wb");
    if(!outVideoFp) {
        fprintf(stderr, "fopen file %s error\n", videoDstFilename);
        return EXIT_FAILURE;
    }

    outAudioFp = fopen(audioDstFilename, "wb");
    if(!outAudioFp) {
        fprintf(stderr, "fopen file %s error\n", audioDstFilename);
        return EXIT_FAILURE;
    }

    AVFormatContext  * inFmtCtx = nullptr;
    ret = avformat_open_input(&inFmtCtx, srcFilename, nullptr, nullptr);
    if(ret < 0) {
        fprintf(stderr, "Could not open source file %s\n", srcFilename);
        exit(1);
    }

    ret = avformat_find_stream_info(inFmtCtx, nullptr);
    if(ret < 0) {
        fprintf(stderr, "Could not find stream information.\n");
        exit(1);
    }

    int videoStreamIdx, audioStreamIdx;
    AVCodecContext * videoCodecCtx = nullptr, *audioCodecCtx = nullptr;
    AVStream * videoStream, * audioStream;
    //打开视频解码器
    if(openCodecContext(&videoStreamIdx, &videoCodecCtx, inFmtCtx, AVMEDIA_TYPE_VIDEO) >=0) {
        videoStream = inFmtCtx->streams[videoStreamIdx];

        int width = videoCodecCtx->width;
        int height = videoCodecCtx->height;
        pix_fmt = videoCodecCtx->pix_fmt;

        ret = av_image_alloc(video_dst_data, video_dst_linesize,
                             width, height, pix_fmt, 1);
        if(ret < 0) {
            fprintf(stderr, "Could not allocate raw video buffer\n");
            return EXIT_FAILURE;
        }
        video_dst_bufsize = ret;
    }

    //打开音频解码器
    if(openCodecContext(&audioStreamIdx, &audioCodecCtx, inFmtCtx, AVMEDIA_TYPE_AUDIO) >= 0) {
        audioStream = inFmtCtx->streams[audioStreamIdx];
    }
    // 打印输入流媒体信息
    av_dump_format(inFmtCtx, -1, srcFilename, 0);

    if(!videoStream && !audioStream) {
        fprintf(stderr, "Could not find audio or video stream in the input.\n");
        exit(1);
    }

//    //分配AVFrame的空间
//    AVFrame * frame = av_frame_alloc();
//    if(!frame) {
//        fprintf(stderr, "Could not allocate AVFrame\n");
//        exit(1);
//    }
    //初始化AVPacket
    AVPacket * pkt = av_packet_alloc();
    if(!pkt) {
        fprintf(stderr, "Could not allocate AVPacket\n");
        exit(1);
    }
    int count = 0;

    while(av_read_frame(inFmtCtx, pkt) >= 0) {
        printf("count: %d\n", ++count);
        if(pkt->stream_index == videoStreamIdx)
            ret = decodePacket(videoCodecCtx, pkt);//执行解码
        else if(pkt->stream_index == audioStreamIdx)
            ret = decodePacket(audioCodecCtx, pkt);

        av_packet_unref(pkt);
        if(ret < 0)
            break;
    }

    //刷新解码器
    if(videoCodecCtx)
    {    decodePacket(videoCodecCtx, nullptr);  }
    if(audioCodecCtx)
    {    decodePacket(audioCodecCtx, nullptr);  }

    printf("====== Demuxing succeeded. ======\n");

    if(videoStream) {
        printf(">> Play the output video file with the command:\n"
               "ffplay -f rawvideo -pix_fmt %s -video_size %dx%d %s\n",
               av_get_pix_fmt_name(pix_fmt),
               videoCodecCtx->width, videoCodecCtx->height, videoDstFilename);
    }

    if(audioStream) {
        enum AVSampleFormat sfmt = audioCodecCtx->sample_fmt;
        int nChannels = audioCodecCtx->channels;
        const char * fmt;

        //判断给定的音频采样格式属于哪种类型
        if(av_sample_fmt_is_planar(sfmt)) {
            const char * packed = av_get_sample_fmt_name(sfmt);
            printf("Warning: the sample format the decoder produced is planar "
                   "(%s). This example will output the first channel only.\n",
                   packed ? packed: "?");
            sfmt = av_get_packed_sample_fmt(sfmt);
            nChannels = 1;
        }

        ret = get_format_from_sample_fmt(&fmt, sfmt);
        if(ret < 0) {
            goto end;
        }

        printf(">>Play the output audio file with the command:\n"
               "ffplay -f %s -ac %d -ar %d %s\n",
               fmt, nChannels,
               audioCodecCtx->sample_rate,
               audioDstFilename);
    }

end:
    avcodec_free_context(&videoCodecCtx);
    avcodec_free_context(&audioCodecCtx);
    avformat_close_input(&inFmtCtx);
    //av_frame_free(&frame);
    av_free(video_dst_data[0]);
    return 0;
}


static int openCodecContext(int *stream_idx,
                              AVCodecContext **dec_ctx,
                              AVFormatContext *fmt_ctx,
                              enum AVMediaType type)
{
    int ret, index;
    AVStream * st;
    AVCodec * dec = nullptr;
    AVDictionary * opts = nullptr;

    ret = av_find_best_stream(fmt_ctx, type, -1, -1, nullptr, 0);
    if(ret < 0) {
        fprintf(stderr, "Could not find %s stream\n",
                av_get_media_type_string(type));
        return ret;
    }

    index = *stream_idx = ret;
    st = fmt_ctx->streams[index];//找到对应的流

    //查找解码器
    dec = avcodec_find_decoder(st->codecpar->codec_id);
    if(!dec){
        fprintf(stderr, "Failed to find %s codec\n",
                av_get_media_type_string(type));
        return AVERROR(EINVAL);
    }

    //分配输出的AVCdoecContext空间
    *dec_ctx = avcodec_alloc_context3(dec);
    if(!*dec_ctx) {
        fprintf(stderr, "Failed to allocate the %s codec context\n",
                av_get_media_type_string(type));
        return AVERROR(ENOMEM);
    }

    //将流中的编解码参数拷贝到输出的AVCodecContext中
    ret = avcodec_parameters_to_context(*dec_ctx, st->codecpar);
    if(ret < 0) {
        fprintf(stderr, "Failed to copy %s codec parameters to decoder context\n",
                av_get_media_type_string(type));
        return ret;
    }

    //打开解码器
    ret = avcodec_open2(*dec_ctx, dec, &opts);
    if(ret < 0) {
        fprintf(stderr, "Failed to open %s codec\n",
                av_get_media_type_string(type));
        return ret;
    }

    return 0;
}

static int decodePacket(AVCodecContext *dec, const AVPacket *pkt)
{
    //将压缩编码的数据交给解码器
    int ret = avcodec_send_packet(dec, pkt);
    if(ret < 0) {
        fprintf(stderr, "Error ocurred when avcodec_send_packet\n");
        return ret;
    }

    AVFrame * frame = av_frame_alloc();
    if(!frame) {
        fprintf(stderr, "Could not allocate AVFrame\n");
        exit(1);
    }

    //从解码器中获取所有的每一帧数据(1对多)
    while(ret >= 0) {
        //接收解码后的数据，放在frame中，就是YUV数据/PCM数据
        ret = avcodec_receive_frame(dec, frame);
        if(ret < 0) {
            if(ret == AVERROR_EOF || ret == AVERROR(EAGAIN))
                return 0;
            fprintf(stderr, "Error during decoding\n");
            return ret;
        }

        //解码成功了,就将数据写入到输出文件
        if(dec->codec->type == AVMEDIA_TYPE_VIDEO) {
            ret = outputVideoFrame(frame);
        } else if(dec->codec->type == AVMEDIA_TYPE_AUDIO) {
            ret = outputAudioFrame(frame);
        }

        av_frame_unref(frame);
        if(ret < 0)
        {    return ret;    }
    }
    av_frame_free(&frame);
    return 0;
}

static int outputVideoFrame(AVFrame *frame)
{
    printf("video_frame n: %d coded_n:%d\n",
           video_frame_count++, frame->coded_picture_number);

    av_image_copy(video_dst_data, video_dst_linesize,
                  (const uint8_t**)frame->data, frame->linesize,
                  pix_fmt, frame->width, frame->height);

    fwrite(video_dst_data[0], 1, video_dst_bufsize, outVideoFp);
    return 0;
}


static int outputAudioFrame(AVFrame *frame)
{
    size_t unpadded_linesize = frame->nb_samples * av_get_bytes_per_sample((AVSampleFormat)frame->format);

    printf("audio frame n: %d, nb_samples:%d, pts:%lld\n",
           audio_frame_count++, frame->nb_samples, frame->pts);

    fwrite(frame->extended_data[0], 1, unpadded_linesize, outAudioFp);
    return 0;
}


static int get_format_from_sample_fmt(const char **fmt,
                                      enum AVSampleFormat sample_fmt)
{
    int i;
    struct sample_fmt_entry {
        enum AVSampleFormat sample_fmt; const char *fmt_be, *fmt_le;
    } sample_fmt_entries[] = {
        { AV_SAMPLE_FMT_U8,  "u8",    "u8"    },
        { AV_SAMPLE_FMT_S16, "s16be", "s16le" },
        { AV_SAMPLE_FMT_S32, "s32be", "s32le" },
        { AV_SAMPLE_FMT_FLT, "f32be", "f32le" },
        { AV_SAMPLE_FMT_DBL, "f64be", "f64le" },
    };
    *fmt = NULL;

    for (i = 0; i < FF_ARRAY_ELEMS(sample_fmt_entries); i++) {
        struct sample_fmt_entry *entry = &sample_fmt_entries[i];
        if (sample_fmt == entry->sample_fmt) {
            *fmt = AV_NE(entry->fmt_be, entry->fmt_le);
            return 0;
        }
    }

    fprintf(stderr,
            "sample format %s is not supported as output format\n",
            av_get_sample_fmt_name(sample_fmt));
    return -1;
}


















