#include <stdio.h>

#include <QCoreApplication>

extern "C"
{
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libavcodec/avcodec.h>
#include <libavutil/file.h>
}

#include <string>
using std::string;

int testAVIO()
{
    //printf("network init.\n");
    //初始化网络
    //avformat_network_init();
    //初始化大管家婆AVFormatContext对象
    AVFormatContext * pFmtCtx = avformat_alloc_context();
    if(pFmtCtx == nullptr) {
        return EXIT_FAILURE;
    }
    printf("========== testAVIO() ==========\n");
    AVInputFormat * pInputFmt = nullptr;
    string url("D:\\videos\\ac_wlh.mp4");
    if(avformat_open_input(&pFmtCtx, url.data(), pInputFmt, NULL) < 0) {
        printf("avformat open failed.\n");
        goto quit;
    } else {
        printf("open stream success!\n");
    }

    if(avformat_find_stream_info(pFmtCtx, nullptr) < 0) {
        printf("av_find_stream_info error.\n");
        goto quit;
    } else {
        printf("av_find_stream_info success.\n");
        printf("nb_streams:%d\n", pFmtCtx->nb_streams);
    }


quit:
    avformat_close_input(&pFmtCtx);
    avformat_free_context(pFmtCtx);
    //avformat_network_deinit();

    return 0;
}

int read_packet(void * ptr, uint8_t * buf, int buf_size)
{
    static int total = 0;
    FILE * fp = (FILE*)ptr;
    int sz = fread(buf, 1, buf_size, fp);
    total += sz;
    printf("Read %d bytes, total:%d\n", sz, total);
    return sz;
}

int64_t seek_func(void * opaque, int64_t offset, int whence)
{
    int64_t ret = 0;
    FILE * fp = (FILE*)opaque;
    if(whence == AVSEEK_SIZE) {
        return EXIT_FAILURE;
    }
    fseek(fp, offset, whence);
    ret = ftell(fp);
    printf("ftell pos: %lld\n", ret);
    return ret;
}

int testAVIO2()
{
    printf("==============================\n");
    //FILE * fp = fopen("D:\\Development\\QtFFmpegLearning\\build-2AVIOTest-Desktop_Qt_5_14_2_MinGW_32_bit-Debug\\debug\\ac_wlh480.mp4", "rb");
    //FILE * fp = fopen("D:\\ac_wlh480.mp4", "rb");//可以打开文件，但读取时出错
    //FILE * fp = fopen("output.flv", "rb");//打开文件失败
    FILE * fp = fopen("D:\\videos\\lldq.flv", "rb");//读取本地文件，也是协议的一种
    if(nullptr == fp) {
        printf("open file error\n");
        return EXIT_FAILURE;
    }

    int size = 1024;
    unsigned char * pBuff = (unsigned char *)malloc(size);

    AVIOContext * pIOCtx = avio_alloc_context(
                pBuff,
                size,
                0,
                fp,
                read_packet,
                0,
                seek_func);
    printf("avio_alloc_context end\n");

    AVFormatContext * pFmtCtx = avformat_alloc_context();
    if(pFmtCtx == nullptr) {
        printf("avformat_alloc_context error\n");
        return EXIT_FAILURE;
    }
    printf("avformat_alloc_context end\n");
    pFmtCtx->pb = pIOCtx;//关联绑定在一起
    pFmtCtx->flags = AVFMT_FLAG_CUSTOM_IO;

    AVInputFormat * pInputFmt = nullptr;
    if(avformat_open_input(&pFmtCtx, "", pInputFmt, nullptr) < 0) {
        printf("avformat_open_input error.\n");
        goto quit;
    } else {
        printf("open stream success.\n");
    }

    printf("\navformat_find_stream_info()\n");
    if(avformat_find_stream_info(pFmtCtx, nullptr) < 0) {
        printf("avformat_find_stream_info error\n");
        goto quit;
    } else {
        printf("avformat_find_stream_info success.\n");
        printf("nb_streams: %d\n", pFmtCtx->nb_streams);
    }

quit:
    avformat_close_input(&pFmtCtx);
    avformat_free_context(pFmtCtx);
    free(pBuff);

    return 0;
}


struct buffer_data{
    uint8_t * ptr;
    size_t size;
};

int read_packet2(void * opaque, uint8_t * buf, int buf_size){
    struct buffer_data * bd = (struct buffer_data *)opaque;
    buf_size = FFMIN(buf_size, bd->size);
    if(!buf_size) {
        return AVERROR_EOF;
    }
    printf("ptr:%p,  size:%zu\n", bd->ptr, bd->size);

    memcpy(buf, bd->ptr, buf_size);
    bd->ptr += buf_size;
    bd->size -= buf_size;
}

int testAVIO3()
{   //测试有问题
    printf("========================================\n");
    AVInputFormat * pInputFmt = nullptr;
    size_t buffer_size = 0;
    const char * file_name = "D:\\videos\\lldq-tkdt.mp4";
    //const char * file_name = "D:\\videos\\ac_wlh.flv";

    uint8_t * buffer = nullptr;
    int ret = av_file_map(file_name, &buffer, &buffer_size, 0, nullptr);
    if(ret < 0) {
        return EXIT_FAILURE;
    }

    struct buffer_data bd;
    bd.ptr = buffer;
    bd.size = buffer_size;
    printf("bd.ptr:%p, bd.size:%d\n", buffer, buffer_size);

    //初始化AVForamtContext
    AVFormatContext * pFmtCtx = avformat_alloc_context();
    if(!pFmtCtx) {
        printf("avformat_alloc_context failed!\n");
        ret = AVERROR(ENOMEM);
        return EXIT_FAILURE;
        //goto end;
    }

    size_t avio_ctx_buffer_size = 4096;
    uint8_t * avio_ctx_buffer = (uint8_t*)av_malloc(avio_ctx_buffer_size);
    memset(avio_ctx_buffer, 0, avio_ctx_buffer_size);
    printf("avio_ctx_buffer:%p\n", avio_ctx_buffer);
    if(!avio_ctx_buffer) {
        ret = AVERROR(ENOMEM);
        return EXIT_FAILURE;
        //goto end;
    }

    AVIOContext * avio_ctx = avio_alloc_context(
        avio_ctx_buffer,
        avio_ctx_buffer_size,
        0,
        &bd,
        read_packet2,
        nullptr,
        nullptr);

    if(!avio_ctx) {
        ret = AVERROR(ENOMEM);
        goto end;
    }
    //AVFormatContext绑定AVIOContext
    pFmtCtx->pb = avio_ctx;
    pFmtCtx->flags = AVFMT_FLAG_CUSTOM_IO;


    ret = avformat_open_input(&pFmtCtx, "", pInputFmt, NULL);
    if(ret < 0) {
        fprintf(stderr, "avformat_open_input error.\n");
        goto end;
    }

    printf("\n----1111\n");

    ret = avformat_find_stream_info(pFmtCtx, nullptr);
    if(ret < 0) {
        fprintf(stderr, "avformat_find_stream_info error.\n");
        goto end;
    } else {
        printf("nb->streams: %d\n", pFmtCtx->nb_streams);
    }

    av_dump_format(pFmtCtx, 0, file_name, 0);

end:
    avformat_close_input(&pFmtCtx);
    av_file_unmap(buffer, buffer_size);
    if(avio_ctx) {
        av_freep(&avio_ctx->buffer);
        avio_context_free(&avio_ctx);
    }
//    if(ret < 0) {
//        fprintf(stderr, "Error occurred: %s\n", av_err2str(ret));
//    }
    return 0;
}

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    testAVIO();
    //testAVIO2();
    //return a.exec();
//    testAVIO3();
    return 0;
}
