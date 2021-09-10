//
// Created by skybcyang on 2021/8/30.
//

#ifndef SNIPPETS_BUBBLESORT_H
#define SNIPPETS_BUBBLESORT_H

#include <vector>
#include <iterator>

void BubbleSort(std::vector<int>::iterator start, std::vector<int>::iterator end) {
    for (auto x_iter = start; x_iter+1 < end; x_iter++) {
        for (auto y_iter = x_iter+1; y_iter < end; y_iter++) {
            if (*x_iter > *y_iter){
                std::swap(*x_iter, *y_iter);
            }
        }
    }
}

#endif //SNIPPETS_BUBBLESORT_H
