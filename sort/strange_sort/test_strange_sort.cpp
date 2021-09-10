//
// Created by skybcyang on 2021/8/30.
//

#include "MonkeySort.h"
#include "SleepSort.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("test monkey sort") {
    std::vector<int> arr {1, 2, 5, 4, 7, 6};
    MonkeySort(arr);
    copy(arr.begin(), arr.end(), std::ostream_iterator<int>(std::cout, " "));
}

TEST_CASE("test_sleep_sort") {
    std::vector<int> arr {2, 1, 9, 3, 4, 5, 7};
    SleepSort(arr);
    copy(res.begin(), res.end(), std::ostream_iterator<int>(std::cout, " "));
}
