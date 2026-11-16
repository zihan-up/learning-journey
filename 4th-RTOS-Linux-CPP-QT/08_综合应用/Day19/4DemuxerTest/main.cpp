#include <QCoreApplication>
#include <QDebug>

extern "C"
{
#include <libavformat/avformat.h>
}

static double r2d(AVRational r) {
    return r.den == 0 ? 0 : (double)r.num / (double) r.den;
}

int testDemuxer1()
{
    const char * fileName = "D:\\videos\\ac_wlh.mp4";
    AVDictionary * opts = nullptr;
    AVFormatContext * pFmtCtx = nullptr;

    int ret = avformat_open_input(&pFmtCtx, fileName, nullptr, &opts);
    if(ret !=0) {
        char buf[1024] = {0};
        printf("open %s failed, %s\n", fileName, buf);
        return EXIT_FAILURE;
    }

    qDebug() << "打开媒体文件成功";

    ret = avformat_find_stream_info(pFmtCtx, nullptr);
    if(ret < 0) {
        fprintf(stderr, "avformat_find_stream_info error\n");
        return EXIT_FAILURE;
    }

    qDebug() << "媒体文件名字: " << pFmtCtx->url;
    qDebug() << "音视频流的个数:" << pFmtCtx->nb_streams;
    qDebug() << "媒体文件的平均码率: " << pFmtCtx->bit_rate << "bps";
    qDebug() << "媒体文件总时长: " << pFmtCtx->duration << "微秒";

    int tus = pFmtCtx->duration / AV_TIME_BASE;
    int thh = tus / 3600;
    int tmm = (tus % 3600) / 60;
    int tss = tus % 60;
    qDebug() << "媒体文件总时长: "<< thh << "时" << tmm << "分" << tss << "秒";

#if 1
    for(unsigned int i = 0; i < pFmtCtx->nb_streams; ++i) {
        AVStream * as = pFmtCtx->streams[i];
        if(AVMEDIA_TYPE_AUDIO == as->codecpar->codec_type) {
            //如果是音频流，则打印音频流的信息
            qDebug() << "\n>> 音频信息:";
            qDebug() << "index: " << as->index;
            qDebug() << "音频采样率: " << as->codecpar->sample_rate << "Hz";
            qDebug() << "音频声道数目: " << as->codecpar->channels;

            if(AV_SAMPLE_FMT_FLTP == as->codecpar->format) {
                qDebug() << "音频采样格式: AV_SAMPLE_FMT_FLTP";
            } else if(AV_SAMPLE_FMT_S16P == as->codecpar->format) {
                qDebug() << "音频采样格式： AV_SAMPLE_FMT_S16P";
            }

            if(AV_CODEC_ID_AAC == as->codecpar->codec_id) {
                qDebug() << "音频压缩编码格式:AAC";
            } else if(AV_CODEC_ID_MP3 == as->codecpar->codec_id) {
                qDebug() << "音频压缩编码格式:MP3";
            }

            qDebug() << "as->duration:" << as->duration;//单位为毫秒
            qDebug()<< as->time_base.num << "/" << as->time_base.den;// 1/1000
            qDebug() << "r2d:" << r2d(as->time_base);//0.001
            int durationAudio = as->duration * r2d(as->time_base);
            int thh = durationAudio / 3600;
            int tmm = durationAudio % 3600 / 60;
            int tss = durationAudio % 60;
            qDebug() << "音频总时长:" << thh << "时" << tmm << "分" << tss << "秒";
        } else if(AVMEDIA_TYPE_VIDEO == as->codecpar->codec_type) {
            qDebug() << "\n>> 视频信息:";
            qDebug() << "index: " << as->index;
            qDebug() << "视频帧率:" << r2d(as->avg_frame_rate);
            qDebug() << "视频分辨率:" << as->codecpar->width << "x" <<as->codecpar->height;
            //qDebug() << "视频压缩编码格式:" << as->codecpar->codec_id;
            if(AV_CODEC_ID_H264 == as->codecpar->codec_id) {
                qDebug() << "视频压缩编码格式:H264";
            } else if(AV_CODEC_ID_FLV1 == as->codecpar->codec_id) {
                qDebug() << "视频压缩编码格式:FLV";
            }

            int durationVideoS = as->duration * r2d(as->time_base);
            qDebug() << "视频总时长:" << durationVideoS / 3600 << "时"
                     << durationVideoS % 3600 / 60 << "分"
                     << durationVideoS % 60 << "秒";
        }
     }
#endif
    //退出程序时，回收资源
    if(pFmtCtx) {
        avformat_close_input(&pFmtCtx);
    }

    return 0;
}

int testDemuxer2()
{
    const char * fileName = "D:\\videos\\ac_wlh.mp4";
    AVDictionary * opts = nullptr;
    AVFormatContext * pFmtCtx = nullptr;

    int ret = avformat_open_input(&pFmtCtx, fileName, nullptr, &opts);
    if(ret !=0) {
        char buf[1024] = {0};
        printf("open %s failed, %s\n", fileName, buf);
        return EXIT_FAILURE;
    }

    qDebug() << "打开媒体文件成功" << endl;

    ret = avformat_find_stream_info(pFmtCtx, nullptr);
    if(ret < 0) {
        fprintf(stderr, "avformat_find_stream_info error\n");
        return EXIT_FAILURE;
    }

    qDebug() << "媒体文件名字: " << pFmtCtx->url;
    qDebug() << "音视频流的个数:" << pFmtCtx->nb_streams;
    qDebug() << "媒体文件的平均码率: " << (int64_t)pFmtCtx->bit_rate /1024 << "kbps";
    qDebug() << "媒体文件总时长: " << pFmtCtx->duration << "微秒";

    int tus = pFmtCtx->duration / AV_TIME_BASE;
    int thh = tus / 3600;
    int tmm = (tus % 3600) / 60;
    int tss = tus % 60;
    qDebug() << "媒体文件总时长: "<< thh << "时" << tmm << "分" << tss << "秒";

    //读取音频信息,查找存放音频流的下标
    int audioIndex = av_find_best_stream(pFmtCtx, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);
    if(audioIndex < 0) {
        qDebug() << "av_find_best_stream error:" << av_get_media_type_string(AVMEDIA_TYPE_AUDIO);
        return EXIT_FAILURE;
    }
    AVStream * as = pFmtCtx->streams[audioIndex];
    qDebug() <<"\n=== 音频信息 ===";
    qDebug() << "index: " << as->index;
    qDebug() << "音频采样率: " << as->codecpar->sample_rate << "Hz";
    qDebug() << "音频声道数目: " << as->codecpar->channels;

    if(AV_SAMPLE_FMT_FLTP == as->codecpar->format) {
        qDebug() << "音频采样格式: AV_SAMPLE_FMT_FLTP";
    } else if(AV_SAMPLE_FMT_S16P == as->codecpar->format) {
        qDebug() << "音频采样格式： AV_SAMPLE_FMT_S16P";
    }

    if(AV_CODEC_ID_AAC == as->codecpar->codec_id) {
        qDebug() << "音频压缩编码格式:AAC";
    } else if(AV_CODEC_ID_MP3 == as->codecpar->codec_id) {
        qDebug() << "音频压缩编码格式:MP3";
    }

    if(as->duration != AV_NOPTS_VALUE) {
        int durationAudio = as->duration * r2d(as->time_base);
        int thh = durationAudio / 3600;
        int tmm = durationAudio % 3600 / 60;
        int tss = durationAudio % 60;
        qDebug() << "as->duration:" << as->duration;
        qDebug() << "as->time_base:" << as->time_base.num << "/" << as->time_base.den;
        qDebug() << "音频总时长:" << thh << "时" << tmm << "分" << tss << "秒";
    }

    //读取视频信息
    int videoIndex = av_find_best_stream(pFmtCtx, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
    if(videoIndex < 0) {
        qDebug() << "av_find_best_stream error:" << av_get_media_type_string(AVMEDIA_TYPE_VIDEO);
        return EXIT_FAILURE;
    }
    as = pFmtCtx->streams[videoIndex];
    qDebug() << "\n=== 视频信息===";
    qDebug() << "index: " << as->index;
    qDebug() << "视频帧率:" << r2d(as->avg_frame_rate);
    qDebug() << "视频分辨率:" << as->codecpar->width << "x" <<as->codecpar->height;
    //qDebug() << "视频压缩编码格式:" << as->codecpar->codec_id;
    if(AV_CODEC_ID_H264 == as->codecpar->codec_id) {
        qDebug() << "视频压缩编码格式:H264";
    } else if(AV_CODEC_ID_FLV1 == as->codecpar->codec_id) {
        qDebug() << "视频压缩编码格式:FLV";
    }

    int durationVideoS = as->duration * r2d(as->time_base);
    qDebug() << "视频总时长:" << durationVideoS / 3600 << "时"
             << durationVideoS % 3600 / 60 << "分"
             << durationVideoS % 60 << "秒";

    //退出程序时，回收资源
    if(pFmtCtx) {
        avformat_close_input(&pFmtCtx);
    }

    return 0;
}

int testDemuxer3()
{
    const char * fileName = "D:\\videos\\lldq-tkdt.mp4";
    AVDictionary * opts = nullptr;
    AVFormatContext * pFmtCtx = nullptr;

    int ret = avformat_open_input(&pFmtCtx, fileName, nullptr, &opts);
    if(ret !=0) {
        char buf[1024] = {0};
        printf("open %s failed, %s\n", fileName, buf);
        return EXIT_FAILURE;
    }

    qDebug() << "打开媒体文件成功" << endl;

    ret = avformat_find_stream_info(pFmtCtx, nullptr);
    if(ret < 0) {
        fprintf(stderr, "avformat_find_stream_info error\n");
        return EXIT_FAILURE;
    }

    //打印媒体文件中流的信息
    av_dump_format(pFmtCtx, -1, fileName, 0);

    int audioIndex = av_find_best_stream(pFmtCtx, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);
    int videoIndex = av_find_best_stream(pFmtCtx, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
    qDebug() << endl << "audio index:" << audioIndex << ", video index:" << videoIndex << "\n";
#if 0
    //提取码流， AVPacket是解码之前的数据
    AVPacket * packet = av_packet_alloc();
    int count = 50;
    while(count-- > 0) {
        //该函数执行结束之后，就会获取一帧数据（例如H264的一帧数据）
        //完成的操作称为解封装
        ret = av_read_frame(pFmtCtx, packet);
        if(ret < 0) {
            qDebug() << "av_read_frame end";
            break;
        }

        if(packet->stream_index == audioIndex) {
            qDebug() << "audio pts: " << packet->pts;
            qDebug() << "audio dts: " << packet->dts;
            qDebug() << "audio size:" << packet->size;
            qDebug() << "audio pos: " << packet->pos;
            qDebug() << "audio duration:" <<
            packet->duration * av_q2d(pFmtCtx->streams[audioIndex]->time_base) << "\n";
        } else if(packet->stream_index == videoIndex) {
            qDebug() << "video pts: " << packet->pts;
            qDebug() << "video dts: " << packet->dts;
            qDebug() << "video size:" << packet->size;
            qDebug() << "video pos: " << packet->pos;
            qDebug() << "video duration:" <<
            packet->duration * av_q2d(pFmtCtx->streams[videoIndex]->time_base) << "\n";
        } else {
            qDebug() << "unknow stream index:" << packet->stream_index << endl;
        }
        //解引用
        av_packet_unref(packet);
    }//end of while

    if(packet) {
        av_packet_free(&packet);
    }

#endif
    if(pFmtCtx) {
        avformat_close_input(&pFmtCtx);
    }
    return 0;
}

int main(int argc, char *argv[])
{
//    testDemuxer1();
//    testDemuxer2();
    testDemuxer3();

    return 0;
}
