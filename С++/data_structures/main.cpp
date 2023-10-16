#include <iostream>
#include <vector>
#include "Queue.h"

using std::cin, std::cout;

int main() {
    std::cout << "Hello, World!" << std::endl;
    Queue<int> q{2, 3, 4, 5, 6};
    q.pushFront(11);

    cout << q << '\t' << q.size() << '\n';
    std::vector<int> v;
    v.pop_back();
    return 0;
}
