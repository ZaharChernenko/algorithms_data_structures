#include "SingleLinkedList.h"
#include <iostream>
#include <list>
#include <utility>
using std::cin, std::cout;

int main() {
    SingleLinkedList<std::pair<int, int>> q {{1, 2}};
    auto f {q.begin()};
    f->first = 25;

    for (auto it : q) {
        std::cout << it.first << ' ';
    }
    return 0;
}
