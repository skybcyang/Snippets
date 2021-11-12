//
// Created by skybcyang on 2021/11/13.
//

#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include "thread_guard.h"

TEST_CASE("test_thread_guard") {
    std::thread thread([]() {
        std::cout << "hello world" << std::endl;
    });
    thread_guard threadGuard(thread);
}