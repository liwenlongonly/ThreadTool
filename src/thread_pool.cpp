//
// Created by 李文龙 on 2019/11/30.
//

#include "thread_pool.h"

NS_ILONG_BEGIN

ThreadPool::ThreadPool(size_t num){
    for (int i = 0; i < num; ++i) {
        auto work = std::make_shared<TaskQueue1>();
        works_.push_back(work);
    }
}

ThreadPool::~ThreadPool() {
    close();
}

void ThreadPool::start() {
    for (auto &work:works_) {
        work->start();
    }
}

void ThreadPool::task(TaskQueue1::Task f) {
    int minTaskIndex = 0;
    int minTaskCount = 0;
    for (int i = 0; i < works_.size(); ++i) {
        int num = works_[i]->taskCount();
        if(num <= 0){
            minTaskIndex = i;
            minTaskCount = num;
            break;
        } else if(num < minTaskCount){
            minTaskIndex = i;
            minTaskCount = num;
        }
    }
    works_[minTaskIndex]->task(f);
}

void ThreadPool::close() {
    for (auto &work:works_) {
        work->close();
    }
}

NS_ILONG_END