#include <iostream>
#include "Queue.h"

using std::cin, std::cout;


int main() {
    Queue<int> q{0, 1, 2, 3};
    q.insert(2, 23);
    q.del(3);
    cout << q << '\n' << q.size() << '\n';
    return 0;
}
