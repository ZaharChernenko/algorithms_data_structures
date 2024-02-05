#pragma once
#include <cstddef>
#include <cstdlib>
#include <utility>
#include <vector>


template <class T>
void merge(const std::vector<T>& left, const std::vector<T>& right, std::vector<T>& arr) {
    std::size_t left_index {0}, right_index {0}, arr_index {0};

    while (left_index != left.size() && right_index != right.size()) {
        if (left[left_index] <= right[right_index]) arr[arr_index++] = left[left_index++];
        else arr[arr_index++] = right[right_index++];
    }

    while (left_index != left.size()) arr[arr_index++] = left[left_index++];
    while (right_index != right.size()) arr[arr_index++] = left[right_index++];
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


template <class T>
std::size_t partition(std::vector<T>& arr, const std::size_t& left, const std::size_t& right) {
    std::size_t equal_index {left}, greater_index {left};
    T pivot {arr[std::rand() % (right - left) + left]};

    for (std::size_t i = left; i != right; ++i) {
        if (arr[i] < pivot) {
            std::swap(arr[greater_index], arr[i]);
            std::swap(arr[equal_index++], arr[greater_index++]);
        }
        else if (arr[i] == pivot) std::swap(arr[greater_index++], arr[i]);
    }

    return equal_index;
}


template <class T>
void _hoarSort(std::vector<T>& arr, const std::size_t& left, const std::size_t& right) {
    if (left < right) {
        std::size_t sorted_index = partition(arr, left, right);
        _hoarSort(arr, left, sorted_index);
        _hoarSort(arr, sorted_index + 1, right);
    }
}


template <class T>
void hoarSort(std::vector<T> &arr) {
    _hoarSort(arr, 0, arr.size());
}

