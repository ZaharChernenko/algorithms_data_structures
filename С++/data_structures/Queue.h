#pragma once
#include <iostream>
#include <exception>
#include <unordered_map>
#include <string>


enum QueueErrors {
    POP_FROM_EMPTY_QUEUE = 1,
    QUEUE_INDEX_OUT_OF_RANGE = 2
};


class QueueException: public std::exception {
private:
    std::unordered_map<QueueErrors, char*> errors_map{{POP_FROM_EMPTY_QUEUE, "\nPop from empty queue\n"},
                                                             {QUEUE_INDEX_OUT_OF_RANGE, "\nQueue index out of range\n"}};
    char* _msg;
public:
    QueueException(QueueErrors e): _msg{errors_map[e]} {};
    [[nodiscard]] const char* what() const noexcept override {
        return _msg;
    }
};


template <class T>
class Queue {
private:
    struct Node {
        T val;
        Node* next;
        Node(const T& val={}, Node* next={nullptr});
    };

    Node* _front;
    Node* _back;
    std::size_t _size;

public:
    Queue();
    Queue(std::initializer_list<T> args);
    ~Queue();
    T& operator[](const std::size_t&  index);

    template<class T1> friend std::ostream& operator<<(std::ostream& os, const Queue<T1>& q);

    [[nodiscard]] std::size_t size() const;

    void pushFront(const T& val);
    void pushBack(const T& val);
    T popFront();
    T popBack();
    T front() const;
    T back() const;
};


template <class T>
Queue<T>::Node::Node(const T& val, Node* next):
    val{val}, next{next} {}


template <class T>
Queue<T>::Queue():
    _front{nullptr}, _back{nullptr}, _size{0} {
    std::cout << "Default constructor was used\n";
}


template <class T>
Queue<T>::Queue(std::initializer_list<T> args):
    _front{new Node(*args.begin())}, _back{_front}, _size{1} {
    for (auto i = args.begin() + 1; i != args.end(); ++i) {
        this->pushBack(*i);
    }
    std::cout << "Constructor with args was used\n";
}


template <class T>
Queue<T>::~Queue() {
    Node* temp = _front;
    while (_front != nullptr) {
        _front = _front->next;
        delete temp;
        temp = _front;
    }
    _back = nullptr;
    std::cout << "Destructor was called\n";
}


template <class T>
T& Queue<T>::operator[](const std::size_t& index) {
    try {
        if (index > _size - 1) throw QueueException(QueueErrors::QUEUE_INDEX_OUT_OF_RANGE);
        Node* temp = _front;
        for (std::size_t i = 0; i < index; ++i) {
            temp = temp->next;
        }
        return temp->val;
    }
    catch (const QueueException e) {
        std::cerr << e.what();
        exit(QueueErrors::QUEUE_INDEX_OUT_OF_RANGE);
    }
}


template <class T1>
std::ostream& operator<<(std::ostream& os, const Queue<T1>& q) {
    os << '[';
    auto temp = q._front;
    while (true) {
        os << temp->val;
        temp = temp->next;
        if (temp == nullptr) break;
        os << ", ";
    }
    return os << ']';
}


template <class T>
std::size_t Queue<T>::size() const {
    return _size;
}


template <class T>
void Queue<T>::pushFront(const T& val) {
    if (_front == nullptr) {
        _back = _front = new Node(val);
        ++_size;
    }
    else {
        _front = new Node(val, _front);
        ++_size;
    }
}


template <class T>
void Queue<T>::pushBack(const T& val) {
    if (_front == nullptr) {
        _back = _front = new Node(val);
        ++_size;
    }
    else {
        _back->next = new Node(val);
        _back = _back->next;
        ++_size;
    }
}


template <class T>
T Queue<T>::popFront() {
    try {
        if (_front == nullptr) {
            throw QueueException(QueueErrors::POP_FROM_EMPTY_QUEUE);
        }
        Node* temp = _front;
        T val = _front->val;
        _front = _front->next;
        delete temp;
        --_size;
        if (_size == 0) _back = _front;
        return val;
    }
    catch (const QueueException& e) {
        std::cerr << e.what();
        exit(QueueErrors::POP_FROM_EMPTY_QUEUE);
    }
}


template <class T>
T Queue<T>::popBack() {
    try {
        if (_front == nullptr) {
            throw QueueException(QueueErrors::POP_FROM_EMPTY_QUEUE);
        }
        T val = _back->val;
        --_size;
        if (_size == 0) {
            delete _back;
            _front = _back = nullptr;
        }
        else {
            Node* temp = _back;
            _back = _front;
            while (_back->next != temp) {
                _back = _back->next;
            }
            _back->next = nullptr;
            delete temp;
        }
        return val;
    }
    catch (const QueueException& e) {
        std::cerr << e.what();
        exit(QueueErrors::POP_FROM_EMPTY_QUEUE);
    }
}


template <class T>
T Queue<T>::front() const {
    try {
        if (_front == nullptr) throw QueueException(QueueErrors::QUEUE_INDEX_OUT_OF_RANGE);
        return _front->val;
    }
    catch (const QueueException e) {
        std::cerr << e.what();
        exit(QueueErrors::QUEUE_INDEX_OUT_OF_RANGE);
    }
}


template <class T>
T Queue<T>::back() const {
    try {
        if (_front == nullptr) throw QueueException(QueueErrors::QUEUE_INDEX_OUT_OF_RANGE);
        return _back->val;
    }
    catch (const QueueException e) {
        std::cerr << e.what();
        exit(QueueErrors::QUEUE_INDEX_OUT_OF_RANGE);
    }
}
