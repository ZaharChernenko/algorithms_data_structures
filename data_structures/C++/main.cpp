#include "SingleLinkedList.h"
#include <iostream>
#include <list>
#include <utility>
using std::cin, std::cout;

int main() {
    SingleLinkedList<std::pair<int, int>> q {{1, 2}, {3, 3}, {4, 4}};
    std::list<int> l;
    auto f {q.cbegin()};
    // f->first = 25;

    for (; f != q.cend(); ++f) {
        std::cout << f->first << ' ';
    }
    return 0;
}
