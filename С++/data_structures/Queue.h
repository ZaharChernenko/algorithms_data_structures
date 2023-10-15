#pragma once
#include <iostream>

template <typename T>
class Queue {
private:
    struct Node {
        T val;
        Node* next;
        Node(T val);
    };

    Node* _head, _tail;
    std::size_t _size;

public:
    Queue();
    void pushBack(T val);
};