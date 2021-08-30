//
// Created by skybcyang on 2021/8/30.
//

#include "BubbleSort.h"
#include <iostream>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("test_bubble_sort") {
    std::vector<int> testArr{3, 2, 4, 1};
    BubbleSort(testArr.begin(), testArr.end());
    copy(testArr.begin(), testArr.end(), std::ostream_iterator<int>(std::cout, " "));
}

