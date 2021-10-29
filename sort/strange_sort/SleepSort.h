//
// Created by skybcyang on 2021/8/30.
//

#ifndef SNIPPETS_SLEEPSORT_H
#define SNIPPETS_SLEEPSORT_H

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <catch2/catch_test_macros.hpp>

template<typename T>
void SleepThread(int input, std::vector<T>& res, std::mutex& m) {
    std::this_thread::sleep_for(std::chrono::seconds(input));
    std::lock_guard<std::mutex> lock(m);
    res.push_back(input);
}

// only when T is Integer
template<typename T>
void SleepSort(std::vector<T>& arr) {
    std::mutex m;
    std::vector<T> res;
    std::vector<std::thread> threads;
    threads.reserve(arr.size());
    for (auto x : arr) {
        threads.emplace_back(std::move(std::thread(SleepThread<T>, x, std::ref(res), std::ref(m))));
    }
    for (auto& t: threads) {
        t.join();
    }
    copy(res.begin(), res.end(), arr.begin());
}
#endif