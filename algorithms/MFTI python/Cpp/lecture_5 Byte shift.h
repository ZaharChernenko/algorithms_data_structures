#pragma once
#include <algorithm>
#include <math.h>

template <class T>
void reverseArr(T* const arr, std::size_t size) {
    for (std::size_t i {0}; i != size / 2; ++i)
        std::swap(*(arr + i), *(arr + size - 1 - i));
}

template <class T>
void moveLeft(T* const arr, std::size_t size) {
    T stash {*arr};

    for (std::size_t i {1}; i != size; ++i)
        *(arr + i - 1) = *(arr + i);
    *(arr + size - 1) = stash;
}

template <class T>
void moveRight(T* const arr, std::size_t size) {
    T stash {*(arr + size - 1)};

    for (std::size_t i {size - 2}; i != std::numeric_limits<std::size_t>::max(); --i)
        *(arr + i + 1) = *(arr + i);
    *arr = stash;
}

bool isPrime(int num) {
    for (int delimeter {2}; delimeter != static_cast<int>(std::sqrt(num)) + 1; ++delimeter)
        if (num % delimeter == 0)
            return false;
    return true;
}

bool* primesArr(int upper_bound) {
    bool* primes_arr {new bool[upper_bound + 1]};
    for (int i {2}; i != upper_bound + 1; ++i)
        *(primes_arr + i) = true;

    for (int i {2}; i != static_cast<int>(std::sqrt(upper_bound)) + 1; ++i) {
        if (*(primes_arr + i))
            for (int j {i * i}; j <= upper_bound; j += i)
                *(primes_arr + j) = false;
    }

    return primes_arr;
}