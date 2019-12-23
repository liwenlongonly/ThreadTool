//
// Created by 李文龙 on 2019/12/1.
//

#ifndef THREAD_TOOL_TEST_TASK_QUEUE_TEST_H
#define THREAD_TOOL_TEST_TASK_QUEUE_TEST_H

#include <gtest/gtest.h>
#include <task_queue.h>
#include <common.h>
#include <chrono>
#include <string>

static uint64_t GetTimestampMs() {
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    return ms.count();
}

class TaskQueueTest1: public testing::Test{
protected:
    virtual void SetUp() override {
        task_queue_ = std::make_shared<ilong::TaskQueue>();
        task_queue_->start();
        LOGD("task start");
    }
    virtual void TearDown() override {
        int count = task_queue_->taskCount();
        LOGD("task end count: %d", count);
        task_queue_->stop();
        task_queue_.reset();
    }
    std::shared_ptr<ilong::TaskQueue> task_queue_;
};

TEST_F(TaskQueueTest1, Test1){
    for (int i = 0; i < 10; ++i) {
        LOGD("start index: %d", i);
        task_queue_->task([i](){
            LOGD("end index: %d", i);
        });
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

TEST_F(TaskQueueTest1, Test2){
    for (int i = 0; i < 10; ++i) {
        LOGD("start index: %d", i);
        task_queue_->task([i](){
            LOGD("end index: %d", i);
        }, 200);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

class TaskQueueTest2: public testing::Test{
protected:
    static void  SetUpTestCase(){
        task_queue_ = new (std::nothrow)ilong::TaskQueue();
        task_queue_->start();
        LOGD("task_queue_ new");
    }
    static void TearDownTestCase(){
        if(task_queue_){
            task_queue_->stop();
            delete task_queue_;
            task_queue_ = nullptr;
        }
        LOGD("delete task_queue_");
    }
    static ilong::TaskQueue * task_queue_;
};

ilong::TaskQueue * TaskQueueTest2::task_queue_ = nullptr;

TEST_F(TaskQueueTest2, Test1){
    for (int i = 0; i < 10; ++i) {
        LOGD("start index: %d", i);
        task_queue_->task([i](){
            LOGD("end index: %d", i);
        });
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

TEST_F(TaskQueueTest2, Test2){
    for (int i = 0; i < 10; ++i) {
        LOGD("start index: %d", i);
        task_queue_->task([i](){
            LOGD("end index: %d", i);
        }, 200);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

TEST_F(TaskQueueTest2, Test3){
    LOGD("current thread is main thread %d", task_queue_->isCurrent());
    task_queue_->task([]{
        LOGD("current thread is task_queue_ %d", task_queue_->isCurrent());
    });
}

#endif //THREAD_TOOL_TEST_TASK_QUEUE_TEST_H
