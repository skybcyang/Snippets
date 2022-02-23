//
// Created by skybcyang on 2021/8/30.
//

#ifndef SNIPPETS_MONKEY_SORT_H
#define SNIPPETS_MONKEY_SORT_H

#include <iostream>
#include <vector>
#include <random>

template<typename T>
void MonkeySort(std::vector<T>& arr) {
    while(!std::is_sorted(arr.begin(), arr.end(), std::less<>())) {
        std::shuffle(arr.begin(), arr.end(), std::mt19937(std::random_device()()));
    }
}
#endif
