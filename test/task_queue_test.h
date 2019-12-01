//
// Created by 李文龙 on 2019/12/1.
//

#ifndef THREAD_TOOL_TEST_TASK_QUEUE_TEST_H
#define THREAD_TOOL_TEST_TASK_QUEUE_TEST_H

#include <gtest/gtest.h>
#include <task_queue.h>
#include <iostream>
#include <chrono>
#include <string>
#include <ctime> //std::localtime
#include <iomanip> //std::put_time
#include <sstream> //std::stringstream

static uint64_t GetTimestampMs() {
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    return ms.count();
}

static const std::string getCurrentSystemDate()
{
    auto tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::stringstream ss;
    ss<<std::put_time(std::localtime(&tt), "%Y-%m-%d %H.%M.%S");
    return ss.str();
}

class TaskQueueTest: public testing::Test{
protected:
    virtual void SetUp()override {
        task_queue_ = std::make_shared<ilong::TaskQueue>();
        task_queue_->start();
    }
    virtual void TearDown() override {
        int count = task_queue_->taskCount();
        std::cout << "task count: " << count << std::endl;
        task_queue_->stop();
        task_queue_.reset();
    }
    std::shared_ptr<ilong::TaskQueue> task_queue_;
};

TEST_F(TaskQueueTest, Test1){
    for (int i = 0; i < 10; ++i) {
        std::cout<<"start:"<<GetTimestampMs()<< " index: "<< i <<std::endl;
        task_queue_->task([i](){
            std::cout<<"end:"<<GetTimestampMs()<< " index: "<< i <<std::endl;
        });
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

TEST_F(TaskQueueTest, Test2){
    for (int i = 0; i < 10; ++i) {
        std::cout<< "start:"<<GetTimestampMs()<< " index: "<< i <<std::endl;
        task_queue_->task([i](){
            std::cout<<"end:"<<GetTimestampMs()<< " index: "<< i <<std::endl;
        }, 200);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

#endif //THREAD_TOOL_TEST_TASK_QUEUE_TEST_H
