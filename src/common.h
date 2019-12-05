//
// Created by 李文龙 on 2019/11/30.
//

#ifndef ASYNC_TASK_POOL_TEST_COMMON_H
#define ASYNC_TASK_POOL_TEST_COMMON_H

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

#endif //ASYNC_TASK_POOL_TEST_COMMON_H
