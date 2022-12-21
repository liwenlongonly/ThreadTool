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
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        LOGD("end ThreadPoolTest1 index 1: %d", std::this_thread::get_id());
    });

    LOGD("start ThreadPoolTest1 index: 2");
    thread_pool_->task([](){
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        LOGD("end ThreadPoolTest1 index 2: %d",std::this_thread::get_id());
    });

    LOGD("start ThreadPoolTest1 index: 3");
    thread_pool_->task([](){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        LOGD("end ThreadPoolTest1 index 3: %d",std::this_thread::get_id());
    });

    LOGD("start ThreadPoolTest1 index: 4");
    thread_pool_->task([](){
        LOGD("end ThreadPoolTest1 index 4: %d",std::this_thread::get_id());
    });

}

#endif //THREAD_TOOL_TEST_THREAD_POOL_TEST_H
