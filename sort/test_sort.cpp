//
// Created by skybcyang on 2021/8/30.
//

#include <iostream>
#include "bubble_sort/bubble_sort.h"
#include "merge_sort/merge_sort.h"
#include "selection_sort/selection_sort.h"
#include "strange_sort/monkey_sort.h"
#include "strange_sort/sleep_sort.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("test_bubble_sort") {
    std::vector<int> testArr{3, 2, 4, 1};
    BubbleSort(testArr);
    copy(testArr.begin(), testArr.end(), std::ostream_iterator<int>(std::cout, " "));
}

TEST_CASE("test_merge_sort") {
    std::vector<int> testArr{3, 2, 4, 5, 7, 1};
    MergeSort(testArr, 0, testArr.size());
    copy(testArr.begin(), testArr.end(), std::ostream_iterator<int>(std::cout, " "));
}

TEST_CASE("test_selection_sort") {
    std::vector<int> testArr{3, 2, 4, 5, 7, 1};
    SelectionSort(testArr);
    copy(testArr.begin(), testArr.end(), std::ostream_iterator<int>(std::cout, " "));
}

TEST_CASE("test monkey sort") {
    std::vector<int> testArr {1, 2, 5, 4, 7, 6};
    MonkeySort(testArr);
    copy(testArr.begin(), testArr.end(), std::ostream_iterator<int>(std::cout, " "));
}

TEST_CASE("test_sleep_sort") {
    std::vector<int> testArr {2, 1, 9, 3, 4, 5, 7};
    SleepSort(testArr);
    copy(testArr.begin(), testArr.end(), std::ostream_iterator<int>(std::cout, " "));
}

