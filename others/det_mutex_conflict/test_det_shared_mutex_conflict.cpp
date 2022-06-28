//
// Created by skybcyang on 2022/6/29.
//

#include <thread>
#include <chrono>
#include <vector>
#include "det_shared_mutex_conflict.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("test det shared mutex conflict") {
    std::shared_mutex shared_mtx;
    using namespace std::chrono_literals;
    std::vector<std::thread> thread_vector;
    for (int i = 0; i < 200000; i++) {
        thread_vector.emplace_back([&shared_mtx]() {
            ReadMutexLock lock(shared_mtx);
            std::this_thread::sleep_for(0.5ms);
        });
    }
    for (int i = 0; i < 200; i++) {
        thread_vector.emplace_back([&shared_mtx]() {
            WriteMutexLock lock(shared_mtx);
            std::this_thread::sleep_for(1ms);
        });
    }
    for(int i = 0; i < 200200; i++) {
        thread_vector[i].join();
    }
}