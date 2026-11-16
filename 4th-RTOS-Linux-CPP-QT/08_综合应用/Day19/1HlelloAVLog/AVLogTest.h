#ifndef AVLOGTEST_H
#define AVLOGTEST_H

#include <stdio.h>
#define __STDC_CONSTANT_MACROS

extern "C"
{
#include <libavutil/avutil.h>
#include <libavutil/opt.h>
#include <libavutil/log.h>
#include <libavutil/parseutils.h>
#include <libavformat/avformat.h>
}
#include <string>
using std::string;
#define AVLogPanic(ctx,msg, ...) av_log(ctx, AV_LOG_PANIC, string("[%s:%d]").append(msg).c_str(), __FILE__, __LINE__, ##__VA_ARGS__);
#define AVLogFatal(ctx,msg, ...) av_log(ctx, AV_LOG_FATAL, string("[%s:%d]").append(msg).c_str(), __FILE__, __LINE__, ##__VA_ARGS__);
#define AVLogError(ctx,msg, ...) av_log(ctx, AV_LOG_ERROR, string("[%s:%d]").append(msg).c_str(), __FILE__, __LINE__, ##__VA_ARGS__);
#define AVLogWarn(ctx,msg, ...) av_log(ctx, AV_LOG_WARNING, string("[%s:%d]").append(msg).c_str(), __FILE__, __LINE__, ##__VA_ARGS__);
#define AVLogInfo(ctx,msg, ...) av_log(ctx, AV_LOG_INFO, string("[%s:%d]").append(msg).c_str(), __FILE__, __LINE__, ##__VA_ARGS__);
#define AVLogVerbose(ctx,msg, ...) av_log(ctx, AV_LOG_VERBOSE, string("[%s:%d]").append(msg).c_str(), __FILE__, __LINE__, ##__VA_ARGS__);
#define AVLogDebug(ctx,msg, ...) av_log(ctx, AV_LOG_DEBUG, string("[%s:%d]").append(msg).c_str(), __FILE__, __LINE__, ##__VA_ARGS__);
#define AVLogTrace(ctx,msg, ...) av_log(ctx, AV_LOG_TRACE, string("[%s:%d]").append(msg).c_str(), __FILE__, __LINE__, ##__VA_ARGS__);


#endif // AVLOGTEST_H
