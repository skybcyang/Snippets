//
// Created by skybcyang on 2021/10/29.
//

#ifndef SNIPPETS_SELECTIONSORT_H
#define SNIPPETS_SELECTIONSORT_H

template<typename T>
void SelectionSort(std::vector<T>& arr) {
    auto i = 0;
    auto j = i;
    for (; i < arr.size(); i++) {
        auto mini = i;
        j = i + 1;
        for(; j < arr.size(); j++) {
            if (arr[j] < arr[mini]) {
                mini = j;
            }
        }
        if (mini != i) {
            std::swap(arr[i], arr[mini]);
        }
    }
}

#endif //SNIPPETS_SELECTIONSORT_H
