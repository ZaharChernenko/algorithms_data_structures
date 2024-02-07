#include <cmath>
#include <iostream>
#include <vector>

template <class T>
void reverse(T& seq) {
    for (int i = 0; i != seq.size() / 2; ++i) {
        std::swap(seq[i], seq[seq.size() - 1 - i]);
    }
}


template <class T>
void moveLeft(T& seq) {
    auto temp = seq[0];

    for (int i = 0; i != seq.size() - 1; ++i) seq[i] = seq[i + 1];
    seq[seq.size() - 1] = temp;
}


template <class T>
void moveRight(T& seq) {
    auto temp = seq[seq.size() - 1];

    for (int i = seq.size() - 1; i != 0; --i) seq[i] = seq[i - 1];
    seq[0] = temp;
}


bool isPrime(int num) {
    for (int i = 2; i <= std::sqrt(num); ++i) {
        if (num % i == 0) return false;
    }
    return true;
}


std::vector<bool> primesVector(int n) {
    std::vector<bool> is_prime_vector(n, true);

    for (int i = 2; i <= std::sqrt(n); ++i) {
        if (is_prime_vector[i]) {
            for (int j = 2 * i; j < n; j += i) is_prime_vector[j] = false;
        }
    }
    return is_prime_vector;
}

