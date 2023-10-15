#include "Queue.h"

template <typename T>
Queue<T>::Node::Node(T val) {
    this->val = val;
    next = nullptr;
}

template <typename T>
Queue<T>::Queue() {
    _head = _tail = nullptr;
    _size = 0;
}

template <typename T>
void Queue<T>::pushBack(T val) {
    if (_head == nullptr) {
        _tail = _head = new Node(val);
        ++_size;
    }
}