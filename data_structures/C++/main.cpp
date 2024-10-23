#include "BinaryTreeRecursive.h"
#include "SingleLinkedList.h"
#include <chrono>
#include <forward_list>
#include <iostream>
#include <set>
#include <vector>

using std::cout;

SingleLinkedList<int> list5() {
    SingleLinkedList<int> temp;
    for (int i {0}; i != 5; ++i)
        temp.push_back(i);
    return temp;
}

void single_linked_list_test() {
    cout << "Тест односвязного списка:\n";
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

    SingleLinkedList<int> test1 {4, 3, 2, 1}, test2 {2, 3, 4, 5};
    SingleLinkedList<int> test3 = test1 = test2; // для test1 вызвался оператор присваивания,
                                                 // а для test3 конструктор копирования

    cout << test3 << '\n';

    SingleLinkedList<int> test4 = list5();
    cout << test4 << '\n';
}

void binary_tree_recursive_test() {
    cout << "Тест бинарного дерева:\n";
    std::chrono::steady_clock::time_point start {std::chrono::steady_clock::now()};
    BinaryTreeRecursive<int> my_t;
    for (int i {0}; i != 10000; ++i)
        my_t.insert(i);
    for (int i {0}; i != 10000; ++i)
        my_t.erase(i);

    cout << "Время моего дерева: "
         << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << '\n';

    start = std::chrono::steady_clock::now();
    std::set<int> std_t;
    for (int i {0}; i != 10000; ++i)
        std_t.insert(i);
    for (int i {0}; i != 10000; ++i)
        std_t.erase(i);
    cout << "Время библиотечного дерева: "
         << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << '\n';

    // не работает, потому что нет шаблонов для разных BinaryTreeRecursive
    // BinaryTreeRecursive<int>::iterator it {BinaryTreeRecursive<double>::iterator()};
    my_t = {1, 2, 3};
    BinaryTreeRecursive<int>::iterator it {my_t.begin()};
    BinaryTreeRecursive<int>::const_iterator cit {};
    cit = it;
    cit = std::move(it);
}

template <typename Iterator>
void print_iterator_info(Iterator it) {
    using traits = std::iterator_traits<Iterator>;
    std::cout << "Value type: " << typeid(typename traits::value_type).name() << std::endl;
    std::cout << "Difference type: " << typeid(typename traits::difference_type).name() << std::endl;
    std::cout << "Pointer type: " << typeid(typename traits::pointer).name() << std::endl;
    std::cout << "Reference type: " << typeid(typename traits::reference).name() << std::endl;
    std::cout << "Iterator category: " << typeid(typename traits::iterator_category).name() << std::endl;
}

int main() {
    print_iterator_info(BinaryTreeRecursive<int>::iterator());
    single_linked_list_test();
    binary_tree_recursive_test();
    return 0;
}
