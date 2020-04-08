//
// Created by 李文龙 on 2019/12/1.
//

#ifndef THREAD_TOOL_TEST_MEMORY_POOL_H
#define THREAD_TOOL_TEST_MEMORY_POOL_H

#include "common.h"
#include <list>
#include <map>
#include <mutex>
#include <memory>
#include <string>

NS_ILONG_BEGIN

template <class T>
class MemoryPool{
public:
    constexpr static int kMaxBufferCount = 30;
    MemoryPool(int maxCount = kMaxBufferCount, const std::string &tag = "");
    virtual ~MemoryPool();
    std::shared_ptr<T> GetObject();
    void ClearAllObjects();
    int GetFreeCount();
    int GetUsedCount();
private:
    std::list<std::shared_ptr<T>> buffers_;
    std::mutex mutex_;
    int max_buffer_count_;

    std::string tag_;
};

NS_ILONG_END

#endif //THREAD_TOOL_TEST_MEMORY_POOL_H
