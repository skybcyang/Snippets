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

std::mutex m;
std::vector<int> res;

void SleepThread(int input) {
    std::this_thread::sleep_for(std::chrono::seconds(input));
    std::lock_guard<std::mutex> lock(m);
    res.push_back(input);
}

void SleepSort(const std::vector<int>& arr) {
    std::vector<std::thread> threads;
    threads.reserve(arr.size());
    for (auto x : arr) {
        threads.emplace_back(std::move(std::thread(SleepThread, x)));
    }
    for (auto& t: threads) {
        t.join();
    }
}
#endif