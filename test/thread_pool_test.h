//
// Created by ilong on 2020/4/8.
//

#ifndef THREAD_TOOL_TEST_THREAD_POOL_TEST_H
#define THREAD_TOOL_TEST_THREAD_POOL_TEST_H

#include <gtest/gtest.h>
#include <thread_pool.h>
#include <common.h>

class ThreadPoolTest1: public testing::Test {
protected:
    virtual void SetUp() override{
        thread_pool_ = std::make_shared<ilong::ThreadPool>(5);
        thread_pool_->start();
    }

    virtual void TearDown() override{
        thread_pool_->close();
    }
    std::shared_ptr<ilong::ThreadPool> thread_pool_;
};

TEST_F(ThreadPoolTest1, Test1){
    LOGD("start ThreadPoolTest1 index: 1");
    thread_pool_->task([](){
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        LOGD("end ThreadPoolTest1 index: 1");
    });

    LOGD("start ThreadPoolTest1 index: 2");
    thread_pool_->task([](){
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        LOGD("end ThreadPoolTest1 index: 2");
    });

}

#endif //THREAD_TOOL_TEST_THREAD_POOL_TEST_H
