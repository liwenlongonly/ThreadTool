//
// Created by ilong on 2020/4/8.
//

#ifndef THREAD_TOOL_TEST_TASK_QUEUE1_H
#define THREAD_TOOL_TEST_TASK_QUEUE1_H

#include "common.h"
#include <atomic>
#include <mutex>
#include <future>
#include <thread>
#include <vector>

class TaskQueue1 {
public:
    using Task = std::function<void >;
    TaskQueue1();
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
    std::vector<Task> tasks_;
    mutable std::mutex task_mutex_;
};


#endif //THREAD_TOOL_TEST_TASK_QUEUE1_H
