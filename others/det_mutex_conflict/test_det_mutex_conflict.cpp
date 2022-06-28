//
// Created by skybcyang on 2022/6/29.
//

#include <thread>
#include <chrono>
#include <vector>
#include "det_mutex_conflict.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("test det mutex conflict") {
    std::mutex mtx;
    using namespace std::chrono_literals;
    std::vector<std::thread> thread_vector;
    for (int i = 0; i < 2000; i++) {
        thread_vector.emplace_back([&mtx]() {
            MutexLock lock(mtx);
            std::this_thread::sleep_for(1ms);
        });
    }
    for(int i = 0; i < 2000; i++) {
        thread_vector[i].join();
    }
}