#include "AVLogTest.h"
#include <QCoreApplication>
#include <QDebug>


void testLog0()
{
    qDebug("==============testLog0()=============");
    int loglevel = av_log_get_level();//32  默认为AV_LOG_INFO级别
    av_log_set_level(AV_LOG_DEBUG);
    loglevel = av_log_get_level();
    av_log(NULL, AV_LOG_PANIC, "Panic: mesage\n");
    av_log(NULL, AV_LOG_FATAL, "Fatal: mesage\n");
    av_log(NULL, AV_LOG_ERROR, "Error: mesage\n");
    av_log(NULL, AV_LOG_WARNING, "Warning: mesage\n");
    av_log(NULL, AV_LOG_INFO, "Info: mesage\n");
    av_log(NULL, AV_LOG_VERBOSE, "Verbose: mesage\n");
    av_log(NULL, AV_LOG_DEBUG, "Debug: mesage\n");
    av_log(NULL, AV_LOG_TRACE, "Trace: message\n");
    qDebug("===============================\n");
}

void testLog1()
{
    qDebug("==============testLog1()===========\n");
    // 设置日志级别为 DEBUG
    av_log_set_level(AV_LOG_DEBUG);
    av_log_set_flags(AV_LOG_PRINT_LEVEL | AV_LOG_SKIP_REPEATED);
    av_log(NULL, AV_LOG_DEBUG, "This is a debug message.\n");
    av_log(NULL, AV_LOG_PANIC, "Panic: mesage\n");
    av_log(NULL, AV_LOG_FATAL, "Fatal: mesage\n");
    av_log(NULL, AV_LOG_ERROR, "Error: mesage\n");
    av_log(NULL, AV_LOG_WARNING, "Warning: mesage\n");
    av_log(NULL, AV_LOG_INFO, "Info: mesage\n");
    av_log(NULL, AV_LOG_VERBOSE, "Verbose: mesage\n");
    av_log(NULL, AV_LOG_DEBUG, "Debug: mesage\n");
    av_log(NULL, AV_LOG_DEBUG, "Debug: mesage\n");
    av_log(NULL, AV_LOG_TRACE, "Trace: message\n");
    qDebug("===============================\n");
}

static
void custom_log_callback1(void *ptr, int level, const char *fmt, va_list vl)
{
    //fprintf(stderr, "[%s:%d] ", __FILE__, __LINE__);
    FILE * fp = fopen("simple_ffmpeg_log.txt", "a+");
    if(fp) {
        vfprintf(fp, fmt, vl);
        fflush(fp);
        fclose(fp);
    }
}

void testLog2()
{
    printf("=================testLog2()===========\n");
    // 设置日志级别为 DEBUG
    av_log_set_level(AV_LOG_DEBUG);
    av_log_set_flags(AV_LOG_PRINT_LEVEL | AV_LOG_SKIP_REPEATED);
    av_log_set_callback(custom_log_callback1);
    av_log(NULL, AV_LOG_DEBUG, "This is a debug message.\n");
    av_log(NULL, AV_LOG_PANIC, "Panic: mesage\n");
    av_log(NULL, AV_LOG_FATAL, "Fatal: mesage\n");
    av_log(NULL, AV_LOG_ERROR, "Error: mesage\n");
    av_log(NULL, AV_LOG_WARNING, "Warning: mesage\n");
    av_log(NULL, AV_LOG_INFO, "Info: mesage\n");
    av_log(NULL, AV_LOG_VERBOSE, "Verbose: mesage\n");
    av_log(NULL, AV_LOG_DEBUG, "Debug: mesage\n");
    av_log(NULL, AV_LOG_DEBUG, "Debug: mesage\n");
    av_log(NULL, AV_LOG_TRACE, "[%s:%d] Trace: message\n", __FILE__, __LINE__);
    printf("===============================\n");
}

void testLog3()
{
    printf("=============testLog3()==============\n");
    AVFormatContext * pAVFmtCtx = avformat_alloc_context();
    // 设置日志级别为 DEBUG
    av_log_set_level(AV_LOG_DEBUG);
    av_log_set_flags(AV_LOG_PRINT_LEVEL | AV_LOG_SKIP_REPEATED);
    av_log(pAVFmtCtx, AV_LOG_DEBUG, "This is a debug message.\n");
    av_log(pAVFmtCtx, AV_LOG_PANIC, "Panic: mesage\n");
    av_log(pAVFmtCtx, AV_LOG_FATAL, "Fatal: mesage\n");
    av_log(pAVFmtCtx, AV_LOG_ERROR, "Error: mesage\n");
    av_log(pAVFmtCtx, AV_LOG_WARNING, "Warning: mesage\n");
    av_log(pAVFmtCtx, AV_LOG_INFO, "Info: mesage\n");
    av_log(pAVFmtCtx, AV_LOG_VERBOSE, "Verbose: mesage\n");
    av_log(pAVFmtCtx, AV_LOG_DEBUG, "Debug: mesage\n");
    av_log(pAVFmtCtx, AV_LOG_DEBUG, "Debug: mesage\n");
    av_log(pAVFmtCtx, AV_LOG_TRACE, "Trace: message\n");
    avformat_free_context(pAVFmtCtx);
    printf("===============================\n");
}

void testLog4()
{
    printf("===============testLog4()============\n");
    av_log_set_level(AV_LOG_TRACE);
    av_log_set_flags(AV_LOG_PRINT_LEVEL);
    AVFormatContext * pAVFmtCtx = avformat_alloc_context();
    AVLogPanic(pAVFmtCtx, "Panic message\n");
    AVLogFatal(pAVFmtCtx, "Fatal message\n");
    AVLogError(pAVFmtCtx, "Error message\n");
    AVLogWarn(pAVFmtCtx, "Warn message\n");
    AVLogInfo(pAVFmtCtx, "Info message\n");
    AVLogDebug(pAVFmtCtx, "Debug message\n");
    AVLogVerbose(pAVFmtCtx, "Verbose message\n");
    AVLogTrace(pAVFmtCtx, "AVLogTrace test\n");
    avformat_free_context(pAVFmtCtx);
    printf("===============================\n");
}


void testDictionary()
{
    AVDictionary * dict = nullptr;
    AVDictionaryEntry * elem = nullptr;

    //添加字段信息
    av_dict_set(&dict, "name", "zhangsan", 0);//字典内部会复制字符串并分配内存
    qDebug() << "1 dict:" << dict << endl;
    av_dict_set(&dict, "age", "22", 0);
    av_dict_set(&dict, "gender", "male", 0);
    av_dict_set(&dict, "phone", "5201314", 0);
    qDebug() << "n dict:" << dict << endl;

    char * k = av_strdup("location");//开辟空间存储字符串
    char * v = av_strdup("wuhan");
    av_dict_set(&dict, k, v, AV_DICT_DONT_STRDUP_KEY | AV_DICT_DONT_STRDUP_VAL);

    printf("================================\n");
    //获取字典中的元素个数
    int cnt = av_dict_count(dict);
    printf("dict counts:%d\n", cnt);


    //printf("遍历字典,扫描每一个字段\n");//中文乱码
    qDebug() << "遍历字典,扫描每一个字段";//这个OK
    while((elem = av_dict_get(dict, "", elem, AV_DICT_IGNORE_SUFFIX)) != nullptr) {
        printf("key:%10s --> value:%s\n", elem->key, elem->value);
    }
    qDebug() << endl;


    printf("================================\n");
    elem = av_dict_get(dict, "name", NULL, 0);//从头开始查找元素
    if(elem)
        printf("elem: %s --> %s\n", elem->key, elem->value);

#if 1
    printf("================================\n");
    av_dict_set(&dict, "phone", NULL, 0);//删除元素
    cnt = av_dict_count(dict);
    printf("dict counts:%d\n", cnt);
    elem = nullptr;
    while((elem = av_dict_get(dict, "", elem, AV_DICT_IGNORE_SUFFIX)) != nullptr) {
        printf("key:%10s --> value:%s\n", elem->key, elem->value);
    }
#endif

    av_dict_free(&dict);
    printf("================================\n");
}

void testParseUtil()
{
    printf("=============testParseUtil()=============\n");
    char inputStr[100] = {0};
    printf("========== Parse Video Size ==========\n");
    int width = 0, height = 0;
    //strcpy(inputStr, "1920x1080");
    //strcpy(inputStr, "hd1080");//同上
    //strcpy(inputStr, "vga");//640x480
    //strcpy(inputStr, "hd720");//1280x720
    //strcpy(inputStr, "pal");//720x576
    strcpy(inputStr, "ntsc");//720x480
    av_parse_video_size(&width, &height, inputStr);
    qDebug() << "width:" << width << ", height:" << height;

    printf("========== Parse Frame Rate ==========\n");
    AVRational outputRatio = {0,0};
    //strcpy(inputStr, "15/1");
    strcpy(inputStr, "ntsc");// 30000/1001
    //strcpy(inputStr, "pal");// 25/1
    av_parse_video_rate(&outputRatio, inputStr);
    qDebug() << "frame rate:" << outputRatio.num << "/" << outputRatio.den;

    printf("========== Parse Time ==========\n");
    int64_t outputTime;
    //strcpy(inputStr, "00:01:01");
    strcpy(inputStr, "00:01:01");
    av_parse_time(&outputTime, inputStr, 1);//单位：微秒
    qDebug() << "microseconds:" << outputTime;

    printf("========== Parse Color ==========\n");
    uint8_t rgbaColor[4] = {0};
    //strcpy(inputStr, "red");
    strcpy(inputStr, "#12345678");
    av_parse_color(rgbaColor, inputStr, -1, NULL);
    printf("(r,g,b,a) is (%d,%d,%d,%d)\n",
           rgbaColor[0], rgbaColor[1], rgbaColor[2], rgbaColor[3]);

    printf("========== Parse ratio ==========\n");
    //strcpy(inputStr, "16:9");
    strcpy(inputStr, "1/25");
    av_parse_ratio(&outputRatio, inputStr, 10000, 0, NULL);
    qDebug() << outputRatio.num << ":" << outputRatio.den;
    printf("=================================\n");
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    testLog0();
//    testLog1();
//    testLog2();
//    testLog3();
//    testLog4();
    testDictionary();
//    testParseUtil();

    return a.exec();
}
