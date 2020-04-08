//
// Created by ilong on 2020/4/8.
//

#include "task_queue1.h"

NS_ILONG_BEGIN

TaskQueue1::TaskQueue1(const std::string &tag):
started_{false},
closed_{false},
tag_{tag}{
    tasks_.clear();
}

TaskQueue1::~TaskQueue1() {
    close();
}

void TaskQueue1::start() {
    if (started_.exchange(true)) {
        return;
    }
    closed_.store(false);
    LOGD("TaskQueue::start().");
    auto promise = std::make_shared<std::promise<void>>();
    thread_ = std::unique_ptr<std::thread>(new std::thread([this, &promise] {
        promise->set_value();
        while (!closed_) {
            //TODO
            Task task;
            {
                std::unique_lock<std::mutex> lock(task_mutex_);
                this->condition_.wait(lock, [this]{ return this->closed_ || !this->tasks_.empty(); });
                task = std::move(this->tasks_.front());
                this->tasks_.pop_front();
            }
            task();
        }
    }));
    promise->get_future().wait();
}

void TaskQueue1::task(Task f) {
    {
        std::unique_lock<std::mutex> lock(task_mutex_);
        tasks_.push_back(f);
    }
    condition_.notify_one();
}

int TaskQueue1::taskCount() const {
    std::unique_lock<std::mutex> lock(task_mutex_);
    return tasks_.size();
}

void TaskQueue1::close() {
    if (!closed_.exchange(true)) {
        condition_.notify_all();
        if (thread_ != nullptr) {
            thread_->join();
        }
        started_.store(false);
        tasks_.clear();
        LOGD("TaskQueue::close().");
    }
}

bool TaskQueue1::isCurrent() const{
    if(thread_){
        std::thread::id current_thread_id = std::this_thread::get_id();
        if(current_thread_id == thread_->get_id()){
            return true;
        }
    }
    return false;
}

NS_ILONG_END