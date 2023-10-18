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
    [[nodiscard]] const char* what() const noexcept override{
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

    Node* _head;
    Node* _tail;
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
    _head{nullptr}, _tail{nullptr}, _size{0} {
    std::cout << "Default constructor was used\n";
}


template <class T>
Queue<T>::Queue(std::initializer_list<T> args):
    _head{new Node(*args.begin())}, _tail{_head}, _size{1} {
    for (auto i = args.begin() + 1; i != args.end(); ++i) {
        this->pushBack(*i);
    }
    std::cout << "Constructor with args was used\n";
}


template <class T>
Queue<T>::~Queue() {
    Node* temp = _head;
    while (_head != nullptr) {
        _head = _head->next;
        delete temp;
        temp = _head;
    }
    _tail = nullptr;
    std::cout << "Destructor was called\n";
}


template <class T>
T& Queue<T>::operator[](const std::size_t& index) {
    try {
        if (index > _size - 1) throw QueueException(QueueErrors::QUEUE_INDEX_OUT_OF_RANGE);
        Node* temp = _head;
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
    auto temp = q._head;
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
    try {
        if (_head == nullptr) {
            throw QueueException(QueueErrors::POP_FROM_EMPTY_QUEUE);
        }
        Node* temp = _head;
        T val = _head->val;
        _head = _head->next;
        delete temp;
        --_size;
        if (_size == 0) _tail = _head;
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
        if (_head == nullptr) {
            throw QueueException(QueueErrors::POP_FROM_EMPTY_QUEUE);
        }
        T val = _tail->val;
        --_size;
        if (_size == 0) {
            delete _tail;
            _head = _tail = nullptr;
        }
        else {
            Node* temp = _tail;
            _tail = _head;
            while (_tail->next != temp) {
                _tail = _tail->next;
            }
            _tail->next = nullptr;
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
        if (_head == nullptr) throw QueueException(QueueErrors::QUEUE_INDEX_OUT_OF_RANGE);
        return _head->val;
    }
    catch (const QueueException e) {
        std::cerr << e.what();
        exit(QueueErrors::QUEUE_INDEX_OUT_OF_RANGE);
    }
}


template <class T>
T Queue<T>::back() const {
    try {
        if (_head == nullptr) throw QueueException(QueueErrors::QUEUE_INDEX_OUT_OF_RANGE);
        return _tail->val;
    }
    catch (const QueueException e) {
        std::cerr << e.what();
        exit(QueueErrors::QUEUE_INDEX_OUT_OF_RANGE);
    }
}
