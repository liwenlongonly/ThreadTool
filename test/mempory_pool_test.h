//
// Created by ilong on 2019/12/11.
//

#ifndef THREAD_TOOL_TEST_MEMPORY_POOL_TEST_H
#define THREAD_TOOL_TEST_MEMPORY_POOL_TEST_H

#include <gtest/gtest.h>
#include <memory_pool.cpp>
#include <common.h>
#include <vector>

class Data{
public:
    Data(){}

    virtual ~Data(){}
};

class MemporyTest1: public testing::Test{
protected:
    virtual void SetUp() override{
        memory_pool_ = std::make_shared<ilong::MemoryPool<Data>>();
    }
    virtual void TearDown() override{

    }
    std::shared_ptr<ilong::MemoryPool<Data>> memory_pool_;
};

TEST_F(MemporyTest1, Test1){
    std::vector<std::shared_ptr<Data>> array(5);
    for (auto &item:array) {
        auto data = memory_pool_->getObject();
        array.push_back(data);
    }
    array.clear();
    std::shared_ptr<Data> data1 = memory_pool_->getObject();
    std::shared_ptr<Data> data2 = memory_pool_->getObject();
    std::shared_ptr<Data> data3 = memory_pool_->getObject();

    EXPECT_EQ(memory_pool_->getFreeCount(), 2);
    EXPECT_EQ(memory_pool_->getUsedCount(), 3);
}

#endif //THREAD_TOOL_TEST_MEMPORY_POOL_TEST_H
