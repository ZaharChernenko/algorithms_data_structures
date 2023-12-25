#include <iostream>
using std::cin, std::cout;

short gcd(const short& a, const short& b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}


int inputB() {
    short a, b, c, d;
    cin >> a >> b >> c >> d;
    short m = a * d + c * b, n = b * d, div = gcd(m, n);
    cout << m / div << ' ' << n / div;
    return 0;
}
