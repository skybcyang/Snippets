//
// Created by skybcyang on 2026/2/23.
//

#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include "lru_cache.h"

TEST_CASE("test_lru_cache basic operations") {
    lru_cache<int, std::string> cache(3);
    
    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(3, "three");
    
    REQUIRE(cache.size() == 3);
    
    auto val1 = cache.get(1);
    REQUIRE(val1.has_value());
    REQUIRE(val1.value() == "one");
    
    auto val2 = cache.get(2);
    REQUIRE(val2.has_value());
    REQUIRE(val2.value() == "two");
}

TEST_CASE("test_lru_cache eviction") {
    lru_cache<int, std::string> cache(2);
    
    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(3, "three"); // Should evict key 1
    
    REQUIRE(cache.size() == 2);
    
    auto val1 = cache.get(1);
    REQUIRE(!val1.has_value()); // Should be evicted
    
    auto val2 = cache.get(2);
    REQUIRE(val2.has_value());
    REQUIRE(val2.value() == "two");
    
    auto val3 = cache.get(3);
    REQUIRE(val3.has_value());
    REQUIRE(val3.value() == "three");
}

TEST_CASE("test_lru_cache update existing key") {
    lru_cache<int, std::string> cache(2);
    
    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(1, "ONE"); // Update key 1
    
    auto val1 = cache.get(1);
    REQUIRE(val1.has_value());
    REQUIRE(val1.value() == "ONE");
    
    cache.put(3, "three"); // Should evict key 2, not key 1
    
    auto val1_again = cache.get(1);
    REQUIRE(val1_again.has_value()); // Key 1 should still exist
    
    auto val2 = cache.get(2);
    REQUIRE(!val2.has_value()); // Key 2 should be evicted
}

TEST_CASE("test_lru_cache access updates order") {
    lru_cache<int, std::string> cache(2);
    
    cache.put(1, "one");
    cache.put(2, "two");
    
    // Access key 1 to make it recently used
    cache.get(1);
    
    cache.put(3, "three"); // Should evict key 2
    
    auto val1 = cache.get(1);
    REQUIRE(val1.has_value()); // Key 1 should still exist
    
    auto val2 = cache.get(2);
    REQUIRE(!val2.has_value()); // Key 2 should be evicted
}
