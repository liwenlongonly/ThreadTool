//
//  main.m
//  AsyncTaskPool
//
//  Created by ilong on 2018/2/7.
//  Copyright © 2018年 ilong. All rights reserved.
//

#include "task_queue_test.h"
#include "mempory_pool_test.h"
#include "thread_pool_test.h"

int main(int argc, const char * argv[]) {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();  // 执行所有的 test case
}
