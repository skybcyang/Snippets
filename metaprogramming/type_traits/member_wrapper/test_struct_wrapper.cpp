//
// Created by skybcyang on 2021/8/7.
//

#include <iostream>
#include "struct_wrapper.h"
#include <catch2/catch_test_macros.hpp>

struct Data {
    int a;
    double b;
};

TEST_CASE("test member wrapper") {
    Data data{};
    IfFieldExistExec(data, a, [&data](auto param) {
        std::cout << "a is exsit" << std::endl;
    });
    IfFieldExistExec(data, b, [&data](auto param) {
        std::cout << "b is exsit" << std::endl;
    });
    IfFieldExistExec(data, c, [&data](auto param) {
        std::cout << "c is exsit" << std::endl;
    });
}