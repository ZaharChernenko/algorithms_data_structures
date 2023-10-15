#include "Queue.h"
#include "iostream"

template <typename T>
Queue<T>::Node::Node():
next{nullptr} {}

template <typename T>
Queue<T>::Node::Node(T val):
val{val}, next{nullptr} {}

template <typename T>
Queue<T>::Queue():
_head{nullptr}, _tail{nullptr}, _size{0} {}

/*template <typename T>
void Queue<T>::pushBack(T val) {
    if (_head == nullptr) {
        _tail = _head = new Node(val);
        ++_size;
    }
}*/