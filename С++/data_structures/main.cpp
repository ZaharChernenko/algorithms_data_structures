#include <iostream>
#include <vector>
#include "Queue.h"

using std::cin, std::cout;


int main() {
    Queue<int> q{2};
    cout << 1 << ' ' << q.popFront() << '\n';
    cout << q << '\t' << q.size() << '\n';
    return 0;
}
