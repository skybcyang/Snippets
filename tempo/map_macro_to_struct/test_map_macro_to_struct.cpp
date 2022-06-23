//
// Created by skybcyang on 2022/6/24.
//

#include "map_macro_to_struct.h"
#include <catch2/catch_test_macros.hpp>


DEFINE_STRUCT(clstemp) {
    DEFINE_FILED(a, int, 1);
    DEFINE_FILED(b, float, 3);
};


TEST_CASE("test map macro to struct") {
    clstemp temp{};
    temp.a = 1;

    temp.b.data[0] = 1.0;
    temp.b.data[1] = 1.0;
    temp.b.len = 2;
}