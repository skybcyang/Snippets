//
// Created by skybcyang on 2021/8/30.
//

#include <iostream>
#include "bubble_sort/BubbleSort.h"
#include "merge_sort/MergeSort.h"
#include "strange_sort/MonkeySort.h"
#include "strange_sort/SleepSort.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("test_bubble_sort") {
    std::vector<int> testArr{3, 2, 4, 1};
    BubbleSort(testArr);
    copy(testArr.begin(), testArr.end(), std::ostream_iterator<int>(std::cout, " "));
}

TEST_CASE("test_merge_sort") {
    std::vector<int> testArr{3, 2, 4, 1};
    MergeSort(testArr, 0, testArr.size());
    copy(testArr.begin(), testArr.end(), std::ostream_iterator<int>(std::cout, " "));
}

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


