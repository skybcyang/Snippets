//
// Created by skybcyang on 2026/2/23.
//

#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include "string_split.h"

TEST_CASE("test_string_split basic") {
    auto result = StringSplit("a,b,c,d", ',');
    REQUIRE(result.size() == 4);
    REQUIRE(result[0] == "a");
    REQUIRE(result[1] == "b");
    REQUIRE(result[2] == "c");
    REQUIRE(result[3] == "d");
}

TEST_CASE("test_string_split empty") {
    auto result = StringSplit("", ',');
    REQUIRE(result.size() == 0);
}

TEST_CASE("test_string_split no delimiter") {
    auto result = StringSplit("hello", ',');
    REQUIRE(result.size() == 1);
    REQUIRE(result[0] == "hello");
}

TEST_CASE("test_string_split_sv") {
    auto result = StringSplitSV("a,b,c", ',');
    REQUIRE(result.size() == 3);
    REQUIRE(result[0] == "a");
    REQUIRE(result[1] == "b");
    REQUIRE(result[2] == "c");
}

TEST_CASE("test_string_split_any") {
    auto result = StringSplitAny("a,b;c|d", ",;|");
    REQUIRE(result.size() == 4);
    REQUIRE(result[0] == "a");
    REQUIRE(result[1] == "b");
    REQUIRE(result[2] == "c");
    REQUIRE(result[3] == "d");
}

TEST_CASE("test_string_trim") {
    REQUIRE(StringTrim("  hello  ") == "hello");
    REQUIRE(StringTrim("\t\nhello\r\n") == "hello");
    REQUIRE(StringTrim("hello") == "hello");
    REQUIRE(StringTrim("   ") == "");
}

TEST_CASE("test_string_join") {
    std::vector<std::string> vec = {"a", "b", "c"};
    REQUIRE(StringJoin(vec, ",") == "a,b,c");
    
    std::vector<std::string> empty;
    REQUIRE(StringJoin(empty, ",") == "");
    
    std::vector<std::string> single = {"hello"};
    REQUIRE(StringJoin(single, ",") == "hello");
}

TEST_CASE("test_parse_number") {
    auto int_val = ParseNumber<int>("42");
    REQUIRE(int_val.has_value());
    REQUIRE(int_val.value() == 42);
    
    auto float_val = ParseNumber<double>("3.14");
    REQUIRE(float_val.has_value());
    REQUIRE(float_val.value() == 3.14);
    
    auto invalid = ParseNumber<int>("abc");
    REQUIRE(!invalid.has_value());
}
