//
// Created by skybcyang on 2023/1/31.
//


#include "mutex_with_count.h"
#include <catch2/catch_test_macros.hpp>
#include <thread>

struct Data{
    int a = 0;
    void Func(int x) {
        std::lock_guard lock(m_mutex);
        a = x;
    }
    MutexWithCount m_mutex;
};

TEST_CASE("test mutex with count") {
    Data data;
    std::vector<std::thread> thread_vec;
    for(int i = 0; i < 100; i++) {
        thread_vec.emplace_back(std::move(std::thread{[&data]() {
            for (int x = 0; x <10000; x++) {
                data.Func(x);
            }
        }}));
    }
    for (auto& thread : thread_vec) {
        thread.join();
    }
}