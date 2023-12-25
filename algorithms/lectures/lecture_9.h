#pragma once
#include <vector>
using std::cin, std::cout;


template <typename T>
void merge(std::vector<T>& vec, const std::vector<T>& left, const std::vector<T>& right) {
    int i1 = 0, i2 = 0, i = 0;
    while (i1 < left.size() && i2 < right.size()) {
        if (left[i1] <= right[i2]) {
            vec[i++] = left[i1++];
        }
        else {
            vec[i++] = right[i2++];
        }
    }
    while (i1 < left.size()) {
        vec[i++] = left[i1++];
    }
    while (i2 < right.size()) {
        vec[i++] = right[i2++];
    }
}


template <typename T>
void mergeSort(std::vector<T>& vec) {
    if (vec.size() <= 1) return;
    std::vector<T> left {vec.begin(), vec.begin() + vec.size() / 2};
    std::vector<T> right {vec.begin() + vec.size() / 2, vec.end()};
    mergeSort(left);
    mergeSort(right);
    merge(vec, left, right);
}


template <typename T>
void hoarSort(std::vector<T>& vec) {
    if (vec.size() <= 1) {
        return;
    }
    T barrier = vec[0];
    std::vector<T> left, middle, right;
    for (const auto& el: vec) {
        if (el < barrier) left.push_back(el);
        else if (el == barrier) middle.push_back(el);
        else right.push_back(el);
    }
    hoarSort(left);
    hoarSort(right);
    vec.clear();
    vec.insert(vec.begin(), left.begin(), left.end());
    vec.insert(vec.end(), middle.begin(), middle.end());
    vec.insert(vec.end(), right.begin(), right.end());
}


void testS() {
    std::vector<int> vec{5, 2, 4, 1, 99, 23, 0};
    mergeSort(vec);
    for (auto el: vec) {
        cout << el << '\n';
    }
}