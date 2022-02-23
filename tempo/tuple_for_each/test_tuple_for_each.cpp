//
// Created by skybcyang on 2020/12/23.
//

#include "tuple_for_each.h"
#include <catch2/catch_test_macros.hpp>
#include <iostream>

template <typename Tuple>
void Print(Tuple&& tuple) {
    ForEach(tuple, [](auto value) {std::cout << value << std::endl;});
}

TEST_CASE("test tuple for each") {
    std::tuple<int, double, std::string> t {1, 2.3, "hello, Ts..."};
    Print(t);
}