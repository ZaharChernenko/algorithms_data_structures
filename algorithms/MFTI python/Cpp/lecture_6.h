#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>


template <class T>
void insertSort(T& seq) {
    std::size_t start;
    for (std::size_t top = 1; top != seq.size(); ++top) {
        start = top;
        while (start != 0 && seq[start] < seq[start - 1]) {
            std::swap(seq[start - 1], seq[start]);
            --start;
        }
    }
}


template <class T>
void choiceSort(T& seq) {
    for (std::size_t pos = 0; pos + 1 != seq.size(); ++pos) {
        for (std::size_t i = pos + 1; i != seq.size(); ++i) {
            if (seq[i] < seq[pos]) std::swap(seq[pos], seq[i]);
        }
    }
}


template <class T>
void bubbleSort(T& seq) {
    for (std::size_t bypass = 0; bypass + 1 != seq.size(); ++bypass) {
        for (std::size_t i = 1; i != seq.size() - bypass; ++i) {
            if (seq[i] < seq[i - 1]) std::swap(seq[i - 1], seq[i]);
        }
    }
}


template <class T>
void bubbleSortCheck(T& seq) {
    bool is_swapped;
    for (std::size_t bypass = 0; bypass + 1 != seq.size(); ++bypass) {
        is_swapped = false;
        for (std::size_t i = 1; i != seq.size() - bypass; ++i) {
            if (seq[i] < seq[i - 1]) {
                is_swapped = true;
                std::swap(seq[i - 1], seq[i]);
            }
        }
        if (!is_swapped) return;
    }
}


void countSort(std::vector<int>& arr) {
    int size {*std::max_element(arr.begin(), arr.end()) + 1};

    std::vector<int> freq_arr(size, 0), pos_arr(size, 0), temp_arr(arr.size(), 0);

    for (const int& elem: arr) ++freq_arr[elem];
    for (int i = 1; i != size; ++i) pos_arr[i] = pos_arr[i - 1] + freq_arr[i - 1];
    for (const int& elem: arr) temp_arr[pos_arr[elem]++] = elem;

    arr = temp_arr;
}

