#include "BinaryTree.h"
#include "Queue.h"
#include <iostream>
using std::cin, std::cout;

int main() {
    Queue<int> q {10, 2, 3, 5};
    cout << q << ' ' << q.size() << '\n';
    return 0;
}
