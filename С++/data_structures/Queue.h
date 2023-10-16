#pragma once
#include <iostream>


template <class T>
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

    template <class T1> friend std::ostream& operator<<(std::ostream& os, const Queue<T1>& q);
    std::size_t size() const;
    void pushBack(T val);
};

template <class T>
Queue<T>::Node::Node():
        next{nullptr} {}


template <class T>
Queue<T>::Node::Node(T val):
        val{val}, next{nullptr} {}


template <class T>
Queue<T>::Queue():
    _head{nullptr}, _tail{nullptr}, _size{0} {}


template <class T1>
std::ostream& operator<<(std::ostream& os, const Queue<T1>& q) {
    auto temp = q._head;
    for (std::size_t i = 0; i < q.size(); ++i) {
        os << temp->val;
        temp = temp->next;
        if (i != q.size() - 1) os << ' ';
    }
    return os;
}


template <class T>
std::size_t Queue<T>::size() const {
    return _size;
}


template <class T>
void Queue<T>::pushBack(T val) {
    if (_head == nullptr) {
        _tail = _head = new Node(val);
        ++_size;
    }
    else {
        _tail->next = new Node(val);
        _tail = _tail->next;
        ++_size;
    }
}