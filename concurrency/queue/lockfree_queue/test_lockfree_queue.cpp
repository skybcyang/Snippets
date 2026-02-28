//
// Created by skybcyang on 2026/2/23.
//

#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <catch2/catch_test_macros.hpp>
#include "lockfree_queue.h"

TEST_CASE("test_bounded_lockfree_queue basic") {
    bounded_lockfree_queue<int, 4> queue;

    REQUIRE(queue.empty());
    REQUIRE(queue.capacity() == 4);

    REQUIRE(queue.try_enqueue(1));
    REQUIRE(queue.try_enqueue(2));
    REQUIRE(queue.try_enqueue(3));
    REQUIRE(queue.try_enqueue(4));

    REQUIRE(queue.size() == 4);

    // Queue is full
    REQUIRE(!queue.try_enqueue(5));

    auto val1 = queue.try_dequeue();
    REQUIRE(val1.has_value());
    REQUIRE(val1.value() == 1);

    // Now we can enqueue again
    REQUIRE(queue.try_enqueue(5));

    auto val2 = queue.try_dequeue();
    REQUIRE(val2.has_value());
    REQUIRE(val2.value() == 2);
}

TEST_CASE("test_bounded_lockfree_queue overwrite protection") {
    bounded_lockfree_queue<int, 2> queue;

    REQUIRE(queue.try_enqueue(1));
    REQUIRE(queue.try_enqueue(2));
    REQUIRE(!queue.try_enqueue(3)); // Full

    auto val = queue.try_dequeue();
    REQUIRE(val.has_value());
    REQUIRE(val.value() == 1);

    REQUIRE(queue.try_enqueue(3)); // Now we can enqueue
}

TEST_CASE("test_bounded_lockfree_queue spsc") {
    bounded_lockfree_queue<int, 1024> queue;
    const int count = 10000;
    std::atomic<int> sum{0};

    std::thread producer([&]() {
        for (int i = 0; i < count; ++i) {
            while (!queue.try_enqueue(i)) {
                // Spin wait
            }
        }
    });

    std::thread consumer([&]() {
        int received = 0;
        while (received < count) {
            auto val = queue.try_dequeue();
            if (val.has_value()) {
                sum += val.value();
                received++;
            }
        }
    });

    producer.join();
    consumer.join();

    REQUIRE(sum == count * (count - 1) / 2);
}

TEST_CASE("test_bounded_lockfree_queue mpmc") {
    bounded_lockfree_queue<int, 1024> queue;
    std::atomic<int> total_enqueued{0};
    std::atomic<int> total_dequeued{0};
    std::atomic<int> sum_dequeued{0};
    const int num_producers = 4;
    const int num_consumers = 4;
    const int items_per_producer = 1000;

    std::vector<std::thread> producers;
    for (int p = 0; p < num_producers; ++p) {
        producers.emplace_back([&, p]() {
            for (int i = 0; i < items_per_producer; ++i) {
                while (!queue.try_enqueue(p * items_per_producer + i)) {
                    // Spin wait when full
                }
                total_enqueued++;
            }
        });
    }

    std::vector<std::thread> consumers;
    for (int c = 0; c < num_consumers; ++c) {
        consumers.emplace_back([&]() {
            while (total_dequeued < num_producers * items_per_producer) {
                auto val = queue.try_dequeue();
                if (val.has_value()) {
                    sum_dequeued += val.value();
                    total_dequeued++;
                }
            }
        });
    }

    for (auto& t : producers) {
        t.join();
    }
    for (auto& t : consumers) {
        t.join();
    }

    REQUIRE(total_enqueued == num_producers * items_per_producer);
    REQUIRE(total_dequeued == num_producers * items_per_producer);
}
