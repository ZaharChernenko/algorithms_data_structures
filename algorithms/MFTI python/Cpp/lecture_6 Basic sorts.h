#include <cstddef>
#include <utility>
#include <vector>

// Сортировка вставками
template <class T>
void insertSort(std::vector<T>& arr) {
    for (std::size_t top {1}; top < arr.size(); ++top) {
        for (std::size_t i {top}; i != 0; --i) {
            if (arr[i - 1] <= arr[i])
                break;
            std::swap(arr[i - 1], arr[i]);
        }
    }
}

template <class T>
void searchSort(std::vector<T>& arr) {
    for (std::size_t pos {0}; pos + 1 < arr.size(); ++pos) {
        for (std::size_t i {pos + 1}; i != arr.size(); ++i)
            if (arr[i] < arr[pos])
                std::swap(arr[i], arr[pos]);
    }
}

template <class T>
void bubbleSort(std::vector<T>& arr) {
    for (std::size_t bypass {0}; bypass + 1 < arr.size(); ++bypass) {
        for (std::size_t i {1}; i != arr.size() - bypass; ++i)
            if (arr[i - 1], arr[i])
                std::swap(arr[i - 1], arr[i]);
    }
}

template <class T>
void bubbleSortWithSortCheck(std::vector<T>& arr) {
    bool is_sorted;
    for (std::size_t bypass {0}; bypass + 1 < arr.size(); ++bypass) {
        is_sorted = true;
        for (std::size_t i {1}; i != arr.size() - bypass; ++i)
            if (arr[i - 1], arr[i]) {
                is_sorted = false;
                std::swap(arr[i - 1], arr[i]);
            }
        if (is_sorted)
            break;
    }
}

void countSort(std::vector<int>& arr) {
    std::vector<size_t> pos_arr(*std::max_element(arr.begin(), arr.end()) + 1);
    for (int& elem : arr)
        ++pos_arr[elem];

    std::size_t prev_pos {0}, prev_count {0}, cur_pos;
    for (size_t& freq : pos_arr) {
        prev_pos = cur_pos = prev_pos + prev_count;
        prev_count = freq;
        freq = cur_pos;
    }

    std::vector<int> temp_arr(arr.size());
    for (int& elem : arr) {
        temp_arr[pos_arr[elem]++] = elem;
    }

    arr = temp_arr;
}