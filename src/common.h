//
// Created by 李文龙 on 2019/11/30.
//

#ifndef ASYNC_TASK_POOL_TEST_COMMON_H
#define ASYNC_TASK_POOL_TEST_COMMON_H

#include <string>
#include <sys/time.h>

#ifdef __cplusplus
#define NS_ILONG_BEGIN                     namespace ilong {
#define NS_ILONG_END                       }
#define USING_NS_ILONG                     using namespace ilong;
#define NS_ILONG                           ::ilong
#else
#define NS_ILONG_BEGIN
#define NS_ILONG_END
#define USING_NS_ILONG
#define NS_ILONG
#endif

static std::string GetFormatDate();

#define LOGTAG   "ILONG_LOG"

#define LOGD(format, ...)   		 printf("%s %s %d %s DEBUG: " format "\n",GetFormatDate().c_str(),__FUNCTION__,__LINE__,LOGTAG, ##__VA_ARGS__)
#define LOGI(format, ...)   		 printf("%s %s %d %s INFO: " format "\n",GetFormatDate().c_str(),__FUNCTION__,__LINE__,LOGTAG, ##__VA_ARGS__)
#define LOGW(format, ...)   		 printf("%s %s %d %s WARNING: " format "\n",GetFormatDate().c_str(),__FUNCTION__,__LINE__,LOGTAG, ##__VA_ARGS__)
#define LOGE(format, ...)   		 printf("%s %s %d %s ERROR: " format "\n",GetFormatDate().c_str(),__FUNCTION__,__LINE__,LOGTAG, ##__VA_ARGS__)

#define CC_CALLBACK_0(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)
#define CC_CALLBACK_1(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
#define CC_CALLBACK_2(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define CC_CALLBACK_3(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)

static std::string GetFormatDate(){
    const int buff_len = 255;
    char tmpBuf[buff_len];
#ifdef WIN32
    SYSTEMTIME sys;
   GetLocalTime(&sys);
   snprintf(tmpBuf, buff_len, "%d-%02d-%02d %02d:%02d:%02d.%03d",
            sys.wYear, sys.wMonth, sys.wDay,
            sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
#else
    struct timeval  tv;
    struct tm       *p;
    gettimeofday(&tv, NULL);
    p = localtime(&tv.tv_sec);
    snprintf(tmpBuf, buff_len, "%d-%02d-%02d %02d:%02d:%02d.%03d",
             1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday,
             p->tm_hour, p->tm_min, p->tm_sec, (int)(tv.tv_usec/1000));
#endif
    return std::string(tmpBuf);
}

#endif //ASYNC_TASK_POOL_TEST_COMMON_H
