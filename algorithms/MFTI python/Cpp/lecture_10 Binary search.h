#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <vector>

template <class T>
std::size_t binarySearch(const std::vector<T>& arr, const T& val) {
    std::size_t left {std::numeric_limits<std::size_t>::max()}, right {arr.size()}, middle;

    while (left + 1 < right) {
        middle = (left + right) >> 1;
        if (arr[middle] < val)
            left = middle;
        else
            right = middle;
    }

    if (right == arr.size() || arr[right] != val)
        return std::numeric_limits<std::size_t>::max();
    return right;
}

template <class T>
std::size_t lowerBound(const std::vector<T>& arr, const T& val) {
    std::size_t left {std::numeric_limits<std::size_t>::max()}, right {arr.size()}, middle;

    while (left + 1 < right) {
        middle = (left + right) >> 1;
        if (arr[middle] < val)
            left = middle;
        else
            right = middle;
    }

    return right;
}

template <class T>
std::size_t upperBound(const std::vector<T>& arr, const T& val) {
    std::size_t left {std::numeric_limits<std::size_t>::max()}, right {arr.size()}, middle;

    while (left + 1 < right) {
        middle = (left + right) >> 1;
        if (arr[middle] > val)
            right = middle;
        else
            left = middle;
    }

    return right;
}

template <class T>
std::size_t count(const std::vector<T>& arr, const T& key) {
    return upperBound(arr, key) - lowerBound(arr, key);
}

uint64_t fib(uint64_t n) {
    uint64_t fib0 {0}, fib1 {1}, temp;

    for (uint64_t i {1}; i != n; ++i) {
        temp = fib0 + fib1;
        fib0 = fib1;
        fib1 = temp;
    }

    return fib1;
}

uint64_t findFib(uint64_t fib_number) {
    uint64_t fib0 {0}, fib1 {1}, fib_index {1}, temp;

    while (fib1 < fib_number) {
        temp = fib0 + fib1;
        fib0 = fib1;
        fib1 = temp;
        ++fib_index;
    }

    return fib_index;
}

int countWays2(uint64_t steps) {
    // сколько способов добраться в координату n,
    // из 1, если можно шагать на 1 или на 2
    std::vector<uint64_t> steps_arr(steps + 1, 0);
    steps_arr[1] = 1;

    for (size_t step {2}; step != steps_arr.size(); ++step) {
        steps_arr[step] = steps_arr[step - 1] + steps_arr[step - 2];
    }

    return steps_arr[steps];
}

int countWaysBool(uint64_t steps, const std::vector<bool>& is_allowed) {
    // сколько способов добраться в координату n,
    // из 1, если можно шагать на 1, 2 и 3,
    // некоторые клетки посещать нельзя
    std::vector<uint64_t> steps_arr(steps + 1, 0);
    steps_arr[1] = 1;
    steps_arr[2] = is_allowed[2];

    for (size_t step {3}; step != steps_arr.size(); ++step) {
        if (is_allowed[step])
            steps_arr[step] = steps_arr[step - 1] + steps_arr[step - 2] + steps_arr[step - 3];
    }

    return steps_arr[steps];
}

uint64_t countMinCost(uint64_t steps, const std::vector<uint64_t>& prices) {
    // минимальная стоимость посещения точки n из точки 1
    std::vector<uint64_t> total_costs(steps + 1, 0);
    total_costs[0] = std::numeric_limits<uint64_t>::max();

    for (size_t step {2}; step != total_costs.size(); ++step) {
        total_costs[step] = prices[step] + std::min(total_costs[step - 1], total_costs[step - 2]);
    }

    return total_costs[steps];
}
