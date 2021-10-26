//
// Created by skybcyang on 2021/10/25.
//

#include <iostream>
#include <future>
#include <thread>
#include <unistd.h>
#include <catch2/catch_test_macros.hpp>

constexpr uint32_t timeout = 5;

void Calc(std::promise<std::vector<int>> p) {
    std::vector<int> results;
    for (int i = 0; i < 6; i++) {
        results.push_back(i);
        sleep(1);
    }
    p.set_value(results);
}

std::vector<int> GetResult() {
    std::vector<int> results;
    std::promise<std::vector<int>> result_promise;
    std::future<std::vector<int>> result_future = result_promise.get_future();
    std::thread t_strategy(&Calc, std::move(result_promise));
    if (result_future.wait_for(std::chrono::seconds(timeout)) == std::future_status::timeout) {
        t_strategy.detach();
        std::cout << "can't get result before time out" << std::endl;
    } else {
        results = result_future.get();
        t_strategy.join();
    }
    return results;
}

TEST_CASE("test timer") {
    std::vector<int> results = GetResult();
    copy(results.begin(), results.end(), std::ostream_iterator<int>(std::cout, " "));
}

