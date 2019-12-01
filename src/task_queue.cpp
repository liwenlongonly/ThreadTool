//
// Created by 李文龙 on 2019/11/30.
//

#include "task_queue.h"

NS_ILONG

TaskQueue::TaskQueue():started_{false}, closed_{false} {

}

TaskQueue::~TaskQueue() {
    stop();
}

void TaskQueue::start() {
    if (started_.exchange(true)) {
        return;
    }
    auto promise = std::make_shared<std::promise<void>>();
    auto work = [this, &promise](){
        promise->set_value();
        std::unique_lock<std::mutex> lock(task_mutex_);
        while (!closed_){
            if(!closed_ && task_queue_.empty()){
                new_task_scheduled_.wait(lock);
            }
            std::chrono::system_clock::time_point time = getFirstTime();
            while (!closed_ && !task_queue_.empty()
                 && new_task_scheduled_.wait_until(lock, time) != std::cv_status::timeout) {
                time = getFirstTime();
            }
            if(closed_){
                break;
            }

            if (task_queue_.empty()) {
                continue;
            }

            Task f = task_queue_.begin()->second;
            task_queue_.erase(task_queue_.begin());

            lock.unlock();
            f();
            lock.lock();
        }
    };
    thread_.reset(new std::thread(work));
    promise->get_future().wait();
}

void TaskQueue::task(TaskQueue::Task f) {
    task(f, 0);
}

void TaskQueue::task(TaskQueue::Task f, int delay_ms) {
    {
        std::lock_guard<std::mutex> lock(task_mutex_);
        task_queue_.insert(std::make_pair(std::chrono::system_clock::now() + std::chrono::milliseconds(delay_ms), f));
    }
    new_task_scheduled_.notify_one();
}

int TaskQueue::taskCount() {
    std::lock_guard<std::mutex> lock(task_mutex_);
    return task_queue_.size();
}

void TaskQueue::stop() {
    if (!closed_.exchange(true)) {
        new_task_scheduled_.notify_all();
        if (thread_ != nullptr) {
            thread_->join();
        }
        task_queue_.clear();
    }
}

std::chrono::system_clock::time_point TaskQueue::getFirstTime() {
    return task_queue_.empty() ? std::chrono::system_clock::now() : task_queue_.begin()->first;
}

END_NS