//
// Created by skybcyang on 2021/8/7.
//

#include <iostream>
#include "enum_wrapper.h"
#include <catch2/catch_test_macros.hpp>

enum E {
    FIRST,
    SECOND
};

TEST_CASE("test enum wrapper") {
    IfEnumExistExec(E, FIRST, [](auto param) {
        std::cout << "FIRST is exist" << std::endl;
    });
    IfEnumExistExec(E, SECOND, [](auto param) {
        std::cout << "SECOND is exist" << std::endl;
    });
    IfEnumExistExec(E, FIRST, [](auto param) {
        std::cout << "FIRST is exist" << std::endl;
    });
}

