#include "Heap.h"
#include "SingleLinkedList.h"
#include <algorithm>
#include <chrono>
#include <forward_list>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using std::cout;

SingleLinkedList<int> list5() {
    SingleLinkedList<int> temp;
    for (int i {0}; i != 5; ++i)
        temp.push_back(i);
    return temp;
}

int main() {
    std::chrono::steady_clock::time_point start {std::chrono::steady_clock::now()};
    SingleLinkedList<int> my_l;
    for (int i {0}; i != 10000; ++i)
        my_l.push_front(i);
    for (int i {0}; i != 10000; ++i)
        my_l.pop_front();
    SingleLinkedList<int>::const_iterator my_start {my_l.before_begin()};
    for (int i {0}; i != 10000; ++i)
        my_l.insert_after(my_start, i);

    cout << "Время моего списка: "
         << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << '\n';

    start = std::chrono::steady_clock::now();
    std::forward_list<int> std_l;
    for (int i {0}; i != 10000; ++i)
        std_l.push_front(i);
    for (int i {0}; i != 10000; ++i)
        std_l.pop_front();
    std::forward_list<int>::const_iterator std_start {std_l.before_begin()};
    for (int i {0}; i != 10000; ++i)
        std_l.insert_after(std_start, i);

    cout << "Время библиотеки: "
         << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << '\n';

    std::forward_list<int>::const_iterator std_it {std_l.cbegin()};
    for (SingleLinkedList<int>::const_iterator my_it {my_l.cbegin()}; my_it != my_l.cend(); ++my_it, ++std_it) {
        if (*my_it != *std_it)
            cout << "ahtung!";
    }

    Heap<int, std::less<int>> h1 {1, 2, 3, 4, -1, -2, -3, 4};
    Heap<int, std::less<int>> h2 {1, 2, 3, -1, -2};

    SingleLinkedList<int> l1 {1, 2, 3};
    std::for_each(l1.begin(), l1.end(), [](int& el) { el = 25; });
    std::cout << l1;

    std::cout << (h1 = std::move(h2)) << '\n';

    while (h1) {
        std::cout << h1.top() << ' ';
        h1.pop();
    }
    return 0;
}
