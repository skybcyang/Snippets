//
// Created by skybcyang on 2021/8/19.
//

#include "calc_array_size.h"
#include <string>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("test_calc_array_size") {
    int a[] = { 1, 2, 3, 4 ,5 };
    std::cout<<arraySize(a)<<std::endl;

    std::string str[] = { "1", "2", "3" };
    std::cout<<arraySize(str)<<std::endl;
}