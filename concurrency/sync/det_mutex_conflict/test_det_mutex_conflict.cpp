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
    const int thread_count = 100;
    
    for (int i = 0; i < thread_count; i++) {
        thread_vector.emplace_back([&mtx]() {
            MutexLock lock(mtx);
            std::this_thread::sleep_for(0.1ms);
        });
    }
    for (auto& t : thread_vector) {
        t.join();
    }
}
