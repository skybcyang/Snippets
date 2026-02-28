//
// Created by skybcyang on 2021/8/15.
//

#include <iostream>
#include "crtp.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("test crtp") {
    AImpl a;
    a.Func();
    BImpl b;
    b.Func();
}

