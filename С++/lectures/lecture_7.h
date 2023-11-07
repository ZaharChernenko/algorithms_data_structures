#pragma once

using std::cin, std::cout;


int fib(int n) {
    if (n == 1 || n == 2) return 1;
    return fib(n - 1) + fib(n - 2);
}


long long factorial(int n) {
    if (n == 1 || n == 0) return 1;
    return factorial(n - 1) * n;
}


template <typename T>
T slowPow(T n, int pow) {
    if (pow == 0) return 1;
    return slowPow(n, pow - 1) * n;
}


template <typename T>
T fastPow(T n, int pow) {
    if (pow == 0) return 1;
    if (pow % 2 == 0) return fastPow(n * n, pow / 2);
    return fastPow(n, pow - 1) * n;
}


int GCD(int a, int b) {
    if (a == b) return a;
    if (a > b) return GCD(a - b, b);
    return GCD(a, b - a);
}


int fasterGCD(int a, int b) {
    if (b == 0) return a;
    return fasterGCD(b, a % b);
}