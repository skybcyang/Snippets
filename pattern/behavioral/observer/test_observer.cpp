//
// Created by skybcyang on 2026/2/23.
//

#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <catch2/catch_test_macros.hpp>
#include "observer.h"

struct temperature_event {
    float celsius;
};

struct message_event {
    std::string sender;
    std::string content;
};

TEST_CASE("test_observer basic") {
    observer<temperature_event> temp_observer;
    int count = 0;
    float last_temp = 0.0f;

    auto callback = [&](const temperature_event& e) {
        count++;
        last_temp = e.celsius;
    };

    temp_observer.subscribe(callback);
    REQUIRE(temp_observer.count() == 1);

    temp_observer.notify(temperature_event{25.5f});
    REQUIRE(count == 1);
    REQUIRE(last_temp == 25.5f);

    temp_observer.notify(temperature_event{30.0f});
    REQUIRE(count == 2);
    REQUIRE(last_temp == 30.0f);
}

TEST_CASE("test_observer multiple callbacks") {
    observer<message_event> msg_observer;
    int count1 = 0;
    int count2 = 0;

    auto callback1 = [&](const message_event&) { count1++; };
    auto callback2 = [&](const message_event&) { count2++; };

    msg_observer.subscribe(callback1);
    msg_observer.subscribe(callback2);
    REQUIRE(msg_observer.count() == 2);

    msg_observer.notify(message_event{"alice", "hello"});
    REQUIRE(count1 == 1);
    REQUIRE(count2 == 1);
}

TEST_CASE("test_observer unsubscribe") {
    observer<temperature_event> temp_observer;
    int count = 0;

    auto callback = [&](const temperature_event&) { count++; };

    auto id = temp_observer.subscribe(callback);
    temp_observer.notify(temperature_event{20.0f});
    REQUIRE(count == 1);

    temp_observer.unsubscribe(id);
    REQUIRE(temp_observer.count() == 0);

    temp_observer.notify(temperature_event{30.0f});
    REQUIRE(count == 1); // Not incremented
}

TEST_CASE("test_observer clear") {
    observer<int> observer;
    int count = 0;

    observer.subscribe([&](int) { count++; });
    observer.subscribe([&](int) { count++; });

    observer.notify(1);
    REQUIRE(count == 2);

    observer.clear();
    REQUIRE(observer.count() == 0);

    observer.notify(1);
    REQUIRE(count == 2); // Not incremented
}

TEST_CASE("test_subscription_guard") {
    observer<int> observer;
    int count = 0;

    auto callback = [&](int) { count++; };

    {
        subscription_guard guard(observer, callback);
        REQUIRE(observer.count() == 1);

        observer.notify(1);
        REQUIRE(count == 1);
    }

    // Guard destroyed, should auto unsubscribe
    REQUIRE(observer.count() == 0);
    observer.notify(1);
    REQUIRE(count == 1); // Not incremented
}

TEST_CASE("test_subscription_guard move") {
    observer<int> observer;
    int count = 0;

    auto callback = [&](int) { count++; };

    subscription_guard guard1(observer, callback);
    REQUIRE(observer.count() == 1);

    auto guard2 = std::move(guard1);
    REQUIRE(observer.count() == 1);

    observer.notify(1);
    REQUIRE(count == 1);
}

TEST_CASE("test_observer_threadsafe") {
    observer_threadsafe<int> observer;
    std::atomic<int> count{0};

    auto callback = [&](int) { count++; };

    auto id = observer.subscribe(callback);
    REQUIRE(observer.count() == 1);

    observer.notify(1);
    REQUIRE(count == 1);

    observer.unsubscribe(id);
    REQUIRE(observer.count() == 0);
}

TEST_CASE("test_observer_threadsafe concurrent notify") {
    observer_threadsafe<int> observer;
    std::atomic<int> count{0};

    observer.subscribe([&](int) { count++; });
    observer.subscribe([&](int) { count++; });

    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&]() {
            for (int j = 0; j < 100; ++j) {
                observer.notify(j);
            }
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    // 10 threads * 100 notifies * 2 callbacks = 2000
    REQUIRE(count == 2000);
}
