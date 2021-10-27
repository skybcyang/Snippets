//
// Created by skybcyang on 2021/8/30.
//

#ifndef SNIPPETS_BUBBLESORT_H
#define SNIPPETS_BUBBLESORT_H

#include <vector>
#include <iterator>

template<typename T>
void BubbleSort(std::vector<T>& input) {
    auto startIter = input.begin();
    auto endIter = input.end();
    for (auto x_iter = startIter; x_iter+1 < endIter; x_iter++) {
        for (auto y_iter = x_iter+1; y_iter < endIter; y_iter++) {
            if (*x_iter > *y_iter){
                std::swap(*x_iter, *y_iter);
            }
        }
    }
}

#endif //SNIPPETS_BUBBLESORT_H
