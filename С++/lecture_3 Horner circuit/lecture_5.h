#pragma once
using std::cin, std::cout;

template <typename T>
void moveRight(T arr[], int size) {
    T temp = arr[size - 1];
    for (int i = size - 1; i > 0; --i) {
        arr[i] = arr[i - 1];
    }
    arr[0] = temp;
}

template <typename T>
void moveLeft(T arr[], int size) {
    T temp = arr[0];
    for (int i = 0; i < size - 1; ++i) {
        arr[i] = arr[i + 1];
    }
    arr[size - 1] = temp;
}

template <typename T>
void reverseArr(T arr[], int size) {
    for (int i = 0; i < size / 2; ++i) {
        T temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

template <typename T>
void printArr(T arr[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << ' ';
    }
    cout << '\n';
}

template <typename T>
void printBoolArr(T arr[], int size) {
    for (int i = 0; i < size; ++i) {
        if (arr[i]) cout << i << '\n';
    }
    cout << '\n';
}

bool isPrime(const int& n) {
    for (int i = 2; i < sqrt(n) + 1; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

bool* primesArr(const int& n) {
    bool* arr = new bool[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = true;
    }

    for (int i = 2; i < n; ++i) {
        if (arr[i]) {
            for (int k = 2 * i; k < n; k += i) {
                arr[k] = false;
            }
        }
    }
    return arr;
}