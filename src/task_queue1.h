//
// Created by ilong on 2020/4/8.
//

#ifndef THREAD_TOOL_TEST_TASK_QUEUE1_H
#define THREAD_TOOL_TEST_TASK_QUEUE1_H

#include <atomic>
#include <memory>
#include <string>
#include <mutex>   // NOLINT
#include <future>  // NOLINT
#include <thread>  // NOLINT
#include <list>
#include "common.h"

NS_ILONG_BEGIN

class TaskQueue1 {
public:
    using Task = std::function<void()>;

    TaskQueue1(const std::string& tag = "");
    virtual ~TaskQueue1();

    virtual void start();

    virtual void close();

    virtual void task(Task f);

    virtual int taskCount() const;

    virtual bool isCurrent() const;

    TaskQueue1(const TaskQueue1&) = delete;
    const TaskQueue1& operator=(const TaskQueue1&) = delete;
private:
    std::atomic<bool> started_;
    std::atomic<bool> closed_;
    std::condition_variable condition_;
    std::unique_ptr<std::thread> thread_;
    std::list<Task> tasks_;
    mutable std::mutex task_mutex_;

    std::string tag_;
};

NS_ILONG_END

#endif //THREAD_TOOL_TEST_TASK_QUEUE1_H
