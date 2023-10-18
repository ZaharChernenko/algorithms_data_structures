#include <iostream>
#include "Queue.h"

using std::cin, std::cout;


int main() {
    Queue<int> q{0, 1, 2, 3};
    q[0] = 25;
    cout << q.back() << '\n';
    cout << q << '\n' << q.size() << '\n';
    return 0;
}
