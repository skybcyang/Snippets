//
// Created by skybcyang on 2021/10/28.
//

#ifndef SNIPPETS_MERGE_SORT_H
#define SNIPPETS_MERGE_SORT_H

template<typename T>
void Merge(std::vector<T>& input, size_t left, size_t mid, size_t right) {
    std::vector<T> tmp;
    size_t pos1 = left, pos2 = mid + 1;
    while (pos1 <= mid && pos2 <= right) {
        if (input[pos1] < input[pos2]) {
            tmp.push_back(input[pos1++]);
        } else {
            tmp.push_back(input[pos2++]);
        }
    }
    while (pos1 <= mid) {
        tmp.push_back(input[pos1++]);
    }
    while (pos2 <= right) {
        tmp.push_back(input[pos2++]);
    }
    std::copy(tmp.begin(), tmp.end(), input.begin() + left);
}

template<typename T>
void MergeSort(std::vector<T>& input, size_t left, size_t right) {
    size_t mid = (left + right) / 2;
    if (left < right) {
        MergeSort(input, left, mid);
        MergeSort(input, mid + 1, right);
        Merge(input, left, mid, right);
    }
}

#endif //SNIPPETS_MERGE_SORT_H
