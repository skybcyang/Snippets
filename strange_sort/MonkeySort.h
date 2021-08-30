//
// Created by skybcyang on 2021/8/30.
//

#ifndef SNIPPETS_MONKEYSORT_H
#define SNIPPETS_MONKEYSORT_H

#include <iostream>
#include <vector>
#include <random>

void MonkeySort(std::vector<int>& arr) {
    while(!std::is_sorted(arr.begin(), arr.end(), std::less<>())) {
        std::shuffle(arr.begin(), arr.end(), std::mt19937(std::random_device()()));
    }
}
#endif
