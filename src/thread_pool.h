//
// Created by 李文龙 on 2019/11/30.
//

#ifndef ASYNC_TASK_POOL_TEST_THREAD_POOL_H
#define ASYNC_TASK_POOL_TEST_THREAD_POOL_H

#include <atomic>
#include <memory>
#include <string>
#include <mutex>   // NOLINT
#include <future>  // NOLINT
#include <thread>  // NOLINT
#include <list>
#include <vector>
#include "common.h"

NS_ILONG_BEGIN

class ThreadPool{
public:
    using Task = std::function<void()>;

    ThreadPool(const size_t num = 1);
    virtual ~ThreadPool();

    virtual void start();

    virtual void task(Task f);

    virtual void close();

    ThreadPool(const ThreadPool&) = delete;
    const ThreadPool& operator=(const ThreadPool&) = delete;
private:
    std::atomic<bool> started_;
    std::atomic<bool> closed_;
    std::condition_variable condition_;
    std::vector<std::unique_ptr<std::thread>> threads_;
    std::list<Task> tasks_;
    mutable std::mutex task_mutex_;
    size_t thread_num_;
};

NS_ILONG_END

#endif //ASYNC_TASK_POOL_TEST_THREAD_POOL_H
