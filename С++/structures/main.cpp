#include <iostream>
#include "Queue.h"

using std::cin, std::cout;

int main() {
    std::cout << "Hello, World!" << std::endl;
    Queue<int> q;
    q.pushBack(12);
    q.pushBack(129);
    cout << q;
    return 0;
}
