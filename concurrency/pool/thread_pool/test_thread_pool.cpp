//
// Created by skybcyang on 2026/2/23.
//

#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include "thread_pool.h"

TEST_CASE("test_thread_pool basic submit") {
    thread_pool pool(2);
    
    auto future1 = pool.submit([]() -> int {
        return 42;
    });
    
    auto future2 = pool.submit([](int a, int b) -> int {
        return a + b;
    }, 10, 20);
    
    REQUIRE(future1.get() == 42);
    REQUIRE(future2.get() == 30);
}

TEST_CASE("test_thread_pool multiple tasks") {
    thread_pool pool(4);
    std::vector<std::future<int>> futures;
    
    for (int i = 0; i < 10; ++i) {
        futures.push_back(pool.submit([i]() -> int {
            return i * i;
        }));
    }
    
    for (int i = 0; i < 10; ++i) {
        REQUIRE(futures[i].get() == i * i);
    }
}

TEST_CASE("test_thread_pool thread count") {
    thread_pool pool(4);
    REQUIRE(pool.thread_count() == 4);
}

TEST_CASE("test_thread_pool void return") {
    thread_pool pool(2);
    int counter = 0;
    
    auto future = pool.submit([&counter]() {
        counter = 100;
    });
    
    future.get();
    REQUIRE(counter == 100);
}

TEST_CASE("test_thread_pool exception handling") {
    thread_pool pool(2);
    
    auto future = pool.submit([]() -> int {
        throw std::runtime_error("test exception");
        return 0;
    });
    
    REQUIRE_THROWS_AS(future.get(), std::runtime_error);
}
