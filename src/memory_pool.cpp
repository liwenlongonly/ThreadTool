//
// Created by 李文龙 on 2019/12/1.
//

#include "memory_pool.h"

NS_ILONG_BEGIN

template <class T>
MemoryPool<T>::MemoryPool(int maxCount, const std::string &tag)
:max_buffer_count_{maxCount},
tag_{tag}{
    buffers_.clear();
}

template <class T>
MemoryPool<T>::~MemoryPool() {
    ClearAllObjects();
}

template <class T>
std::shared_ptr<T> MemoryPool<T>::GetObject(){
    std::lock_guard<std::mutex> guard(mutex_);
    int used_count = buffers_.size();
    if(used_count > max_buffer_count_){
        std::shared_ptr<T> data;
        return data;
    }
    for (const std::shared_ptr<T> &buffer : buffers_) {
        if (buffer.use_count() == 1){
            return buffer;
        }
    }
    std::shared_ptr<T> data = std::make_shared<T>();
    buffers_.push_back(data);
    return data;
}

template <class T>
void MemoryPool<T>::ClearAllObjects(){
    std::lock_guard<std::mutex> guard(mutex_);
    buffers_.clear();
}

template <class T>
int MemoryPool<T>::GetFreeCount(){
    std::lock_guard<std::mutex> guard(mutex_);
    int freeCount = 0;
    for (const std::shared_ptr<T> &buffer : buffers_) {
        if (buffer.use_count() == 1){
            freeCount++;
        }
    }
    return freeCount;
}

template <class T>
int MemoryPool<T>::GetUsedCount(){
    std::lock_guard<std::mutex> guard(mutex_);
    int usedCount = 0;
    for (const std::shared_ptr<T> &buffer : buffers_) {
        if (buffer.use_count() > 1){
            usedCount++;
        }
    }
    return usedCount;
}

NS_ILONG_END