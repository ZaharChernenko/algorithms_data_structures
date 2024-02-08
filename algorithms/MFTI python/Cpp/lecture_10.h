#include <algorithm>
#include <cstddef>
#include <limits>
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
std::size_t upperBound(const std::vector<T>& arr, const T& key) {
    int left = -1, right = arr.size(), middle;
    while (left + 1 < right) {
        middle = (left + right) / 2;
        if (arr[middle] > key) right = middle;
        else left = middle;
    }
    return right;
}


template <class T>
std::size_t count(const std::vector<T>& arr, const T& key) {
    return upperBound(arr, key) - lowerBound(arr, key);
}


int fib(const int& n) {
    int fib0 {0}, fib1 {1}, temp;

    for (int i = 1; i < n; ++i) {
        temp = fib0 + fib1;
        fib0 = fib1;
        fib1 = temp;
    }

    return temp;
}


int findFib(const int& n) {
    int fib0 {0}, fib1 {1}, temp, count {1};

    while (fib1 < n) {
        temp = fib0 + fib1;
        fib0 = fib1;
        fib1 = temp;
        ++count;
    }

    return count;
}


int countWays2(const int& n) {
    // сколько способов добраться в координату n,
    // из 1, если можно шагать на 1 или на 2
    std::vector ways_arr {std::vector(n + 1, 0)};
    ways_arr[1] = 1;

    for (int i = 2; i < n + 1; ++i) {
        ways_arr[i] = ways_arr[i - 1] + ways_arr[i - 2];
    }

    return ways_arr[n];
}


int countWaysBool(const int& n, const std::vector<bool>& allowed) {
    // сколько способов добраться в координату n,
    // из 1, если можно шагать на 1, 2 и 3,
    // некоторые клетки посещать нельзя

    std::vector<int> ways_arr {std::vector(n + 1, 0)};
    ways_arr[1] = 1;
    ways_arr[2] = allowed[1] ? 1 : 0;

    for (int i = 3; i < n + 1; ++i) {
        if (allowed[i - 1]) {
            ways_arr[i] = ways_arr[i - 1] + ways_arr[i - 2] + ways_arr[i - 3];
        }
    }

    return ways_arr[n];
}


int countMinCost(const int& n, const std::vector<int>& prices_arr) {
    // минимальная стоимость посещения точки n из точки 1
    std::vector<int> costs_arr {std::vector(n + 1, 0)};
    costs_arr[0] = std::numeric_limits<int>::max();

    for (int i = 2; i < n + 1; ++i) {
        costs_arr[i] = std::min(costs_arr[i - 1] + prices_arr[i - 2], costs_arr[i - 2] + prices_arr[i - 2]);
    }

    return costs_arr[n];
}
