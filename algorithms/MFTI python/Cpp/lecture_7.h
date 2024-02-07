#include <iostream>


long long fib(int n) {
    if (n == 1 || n == 2) return 1;
    return fib(n - 1) + fib(n - 2);
}


void matreshka(int n) {
    if (!n) {
        std::cout << "Середина\n";
        return;
    }
    std::cout << "Верх матрешки: n = " << n << '\n';
    matreshka(n - 1);
    std::cout << "Низ матрешки: n = " << n << '\n';
}


int pow(int num, int degree) {
    if (!degree) return 1;

    return pow(num, degree - 1) * num;
}


int fasterPow(int num, int degree) {
    if (!degree) return 1;

    if (degree % 2 == 0) return fasterPow(num * num, degree / 2);
    return fasterPow(num, degree - 1) * num;
}


int gcd(int a, int b) {
    if (a == b) return a;

    if (a > b) return gcd(a - b, b);
    return gcd(a, b - a);
}


int fasterGCD(int a, int b) {
    if (b == 0) return a;
    return fasterGCD(b, a % b);
}

