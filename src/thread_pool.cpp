//
// Created by 李文龙 on 2019/11/30.
//

#include "thread_pool.h"

NS_ILONG_BEGIN

ThreadPool::ThreadPool(const size_t num):
started_{false},
closed_{false},
thread_num_{num}{
    tasks_.clear();
    threads_.clear();
}

ThreadPool::~ThreadPool() {
    close();
}

void ThreadPool::start() {
    if (started_.exchange(true)) {
        return;
    }
    threads_.clear();
    closed_.store(false);
    std::vector<std::shared_ptr<std::promise<void>>> promises(thread_num_);
    auto worker = [this](std::shared_ptr<std::promise<void>> &promise){
        promise->set_value();
        while (!closed_) {
            //TODO
            Task task;
            {
                std::unique_lock<std::mutex> lock(task_mutex_);
                this->condition_.wait(lock, [this]{ return this->closed_ || !this->tasks_.empty(); });
                if(this->tasks_.size() <= 0){
                    continue;
                }
                task = std::move(this->tasks_.front());
                this->tasks_.pop_front();
            }
            task();
        }
    };
    for (auto promise:promises) {
        promise = std::make_shared<std::promise<void>>();
        auto thread = std::unique_ptr<std::thread>(new std::thread(worker, std::ref(promise)));
        threads_.push_back(std::move(thread));
    }
    for (auto promise:promises) {
        promise->get_future().wait();
    }
}

void ThreadPool::task(Task f) {
    {
        std::unique_lock<std::mutex> lock(task_mutex_);
        tasks_.push_back(f);
    }
    condition_.notify_one();
}

void ThreadPool::close() {
    if (!closed_.exchange(true)) {
        condition_.notify_all();
        for(auto &thread:threads_){
            if(thread->joinable()){
                thread->join();
            }
        }
        threads_.clear();
        started_.store(false);
        tasks_.clear();
    }
}

NS_ILONG_END