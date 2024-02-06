#include <cstddef>
#include <vector>


template <class T>
int binarySearch(const std::vector<T>& arr, const T& key) {
    int left = -1, right = arr.size(), middle;
    while (left + 1< right) {
        middle = (left + right) / 2;
        if (arr[middle] < key) left = middle;
        else right = middle;
    }
    if (right == arr.size() || arr[right] != key) return -1;
    return right;
}


template <class T>
std::size_t lowerBound(const std::vector<T>& arr, const T& key) {
    int left = -1, right = arr.size(), middle;
    while (left + 1 < right) {
        middle = (left + right) / 2;
        if (arr[middle] < key) left = middle;
        else right = middle;
    }
    return right;
}


template <class T>
int upperBound(const std::vector<T>& arr, const T& key) {
    int left = -1, right = arr.size(), middle;
    while (left + 1 < right) {
        middle = (left + right) / 2;
        if (arr[middle] > key) right = middle;
        else left = middle;
    }
    return right;
}

