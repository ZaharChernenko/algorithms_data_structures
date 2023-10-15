#pragma once
#include <iostream>

template <typename T>
class Queue {
private:
    struct Node {
        T val;
        Node* next;
        Node();
        Node(T val);
    };

    Node* _head;
    Node* _tail;
    std::size_t _size;

public:
    Queue();
    //Queue(T val);
    //void pushBack(T val);
};
