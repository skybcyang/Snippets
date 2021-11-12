//
// Created by skybcyang on 2021/11/13.
//

#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include "thread_task.h"

TEST_CASE("test_thread_task") {
    thread_task([]() { std::cout << "hello, world!" << std::endl; });
}