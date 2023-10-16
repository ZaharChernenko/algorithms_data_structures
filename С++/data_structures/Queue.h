#pragma once
#include <iostream>


template <class T>
class Queue {
private:
    struct Node {
        T val;
        Node* next;
        Node();
        Node(const T& val);
        Node(const T& val, Node* next);
    };

    Node* _head;
    Node* _tail;
    std::size_t _size;

public:
    Queue();
    Queue(std::initializer_list<T> args);

    template <class T1> friend std::ostream& operator<<(std::ostream& os, const Queue<T1>& q);

    std::size_t size() const;

    void pushFront(const T& val);
    void pushBack(const T& val);
    T popFront();
    T popBack();

};


template <class T>
Queue<T>::Node::Node():
        next{nullptr} {}


template <class T>
Queue<T>::Node::Node(const T& val):
        val{val}, next{nullptr} {}


template <class T>
Queue<T>::Node::Node(const T& val, Node* next):
    val{ val }, next{ next } {}


template <class T>
Queue<T>::Queue():
    _head{nullptr}, _tail{nullptr}, _size{0} {
    cout << "Default constructor was used\n";
}


template <class T>
Queue<T>::Queue(std::initializer_list<T> args):
    _head{new Node(*args.begin())}, _tail{_head}, _size{1} {
    for (auto i = args.begin() + 1; i != args.end(); ++i) {
        this->pushBack(*i);
    }
    cout << "Constructor with args was used\n";
}


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
void Queue<T>::pushFront(const T& val) {
    if (_head == nullptr) {
        _tail = _head = new Node(val);
        ++_size;
    }
    else {
        _head = new Node(val, _head);
        ++_size;
    }
}


template <class T>
void Queue<T>::pushBack(const T& val) {
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


template <class T>
T Queue<T>::popFront() {
    try
    {
        if (_head == nullptr) {
            throw 
         }
    }
    catch (const std::exception&)
    {

    }
}
