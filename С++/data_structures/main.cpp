#include <iostream>
#include <vector>
#include "Queue.h"

using std::cin, std::cout;

int main() {
    Queue<int> q{2};
    cout << 1 << ' ' << q.popFront() << '\n';
    cout << 1 << ' ' << q.popFront() << '\n';
    cout << q << '\t' << q.size() << '\n';

    int* arr = new int[10];
    delete[] arr;
    arr = new int[20];
    return 0;
}
