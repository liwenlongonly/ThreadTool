//
// Created by 李文龙 on 2019/11/30.
//

#ifndef ASYNC_TASK_POOL_TEST_THREAD_POOL_H
#define ASYNC_TASK_POOL_TEST_THREAD_POOL_H

#include "common.h"
#include "task_queue1.h"
#include <vector>

NS_ILONG_BEGIN

class ThreadPool{
public:
    ThreadPool(size_t num);
    virtual ~ThreadPool();

    virtual void start();

    virtual void task(TaskQueue1::Task f);

    virtual void close();

private:
    std::vector<std::shared_ptr<TaskQueue1>> works_;
};

NS_ILONG_END

#endif //ASYNC_TASK_POOL_TEST_THREAD_POOL_H
