#pragma once
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <ostream>
#include <stdexcept>

#define DEBUG

template <class T>
class SingleLinkedList {
  protected:
    struct Node {
        T value;
        Node* next;

        Node(const T& value, Node* next = nullptr);
    };

    std::size_t _size;
    Node* _before_front;
    Node* _back;

  public:
    class iterator;
    class const_iterator;

    class iterator {
        friend class SingleLinkedList;

      public:
        using iterator_category = std::forward_iterator_tag; // можно писать typedef
        using difference_type = std::ptrdiff_t;              // но он устарел
        using value_type = T;
        using pointer = T*;
        using reference = T&;

      protected:
        Node* ptr;

      public:
        iterator(Node* ptr);
        iterator(const iterator& other);
        iterator(const const_iterator& other);

        T& operator*();
        T* operator->();
        iterator& operator++();
        [[nodiscard]] iterator operator++(int); // здесь вызывается копирование, поэтому ссылка не нужна
        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;
    };

    class const_iterator {
        friend class SingleLinkedList;

      public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = const T;
        using pointer = const T*;
        using reference = const T&;

      protected:
        Node* ptr;

      public:
        const_iterator(Node* ptr);
        const_iterator(const iterator& other);
        const_iterator(const const_iterator& other);

        const T& operator*();
        const T* operator->(); // указатель на константу
        const_iterator& operator++();
        [[nodiscard]] const_iterator operator++(int); // здесь вызывается копирование, поэтому ссылка не нужна
        bool operator==(const const_iterator& other) const;
        bool operator!=(const const_iterator& other) const;
    };

    SingleLinkedList();
    SingleLinkedList(std::initializer_list<T> list);
    SingleLinkedList(const SingleLinkedList<T>& other);
    SingleLinkedList(const std::size_t& size, const T& default_value = {});
    SingleLinkedList(SingleLinkedList<T>&& other);
    ~SingleLinkedList();

    SingleLinkedList<T>& operator=(const SingleLinkedList<T>& other);
    SingleLinkedList<T>& operator=(SingleLinkedList<T>&& other);
    [[nodiscard]] T& operator[](std::size_t index);
    // нужен для передачи SingleLinkedList<T> const & list (когда нельзя изменять ячейки)
    [[nodiscard]] const T& operator[](std::size_t index) const;

    template <class T1> // дружественные функции необходимо объявлять шаблонными у шаблонного класса
    friend std::ostream& operator<<(std::ostream& os, const SingleLinkedList<T1>& list);

    [[nodiscard]] iterator begin() const;
    [[nodiscard]] iterator end() const;
    [[nodiscard]] iterator before_begin() const;
    [[nodiscard]] const_iterator cbegin() const;
    [[nodiscard]] const_iterator cend() const;
    [[nodiscard]] const_iterator cbefore_begin() const;
    [[nodiscard]] std::size_t size() const;
    [[nodiscard]] bool empty() const;
    [[nodiscard]] T& front(); // т.к. эту функцию можно использовать для записи, метод non-const
    [[nodiscard]] T& front() const;
    [[nodiscard]] T& back();
    [[nodiscard]] T& back() const;

    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();
    void insert_after(const iterator& it, const T& value);
    void insert_after(const const_iterator& it, const T& value);
    void erase_after(const iterator& it);
    void erase_after(const const_iterator& it);
    void reverse();
};

// Node
template <class T> // если не определить то будет warning, что конструктор неопределен
SingleLinkedList<T>::Node::Node(const T& value, Node* next) : value {value}, next {next} {}

// iterator
template <class T>
SingleLinkedList<T>::iterator::iterator(Node* ptr) : ptr {ptr} {}

template <class T>
SingleLinkedList<T>::iterator::iterator(const iterator& other) : ptr {other.ptr} {}

template <class T>
SingleLinkedList<T>::iterator::iterator(const const_iterator& other) : ptr {other.ptr} {}

template <class T>
T& SingleLinkedList<T>::iterator::operator*() {
    return ptr->value; // итератор при разыменовании обратится к полю Node у *ptr
}

template <class T>
T* SingleLinkedList<T>::iterator::operator->() {
    return &(ptr->value);
}

template <class T>
SingleLinkedList<T>::iterator& SingleLinkedList<T>::iterator::operator++() {
    ptr = ptr->next;
    return *this; // т.к. this - указатель на текущий объект, а нам нужен адрес, то используем *
}

template <class T>
SingleLinkedList<T>::iterator SingleLinkedList<T>::iterator::operator++(int) {
    iterator temp {*this};
    ptr = ptr->next;
    return temp;
}

template <class T>
bool SingleLinkedList<T>::iterator::operator==(const iterator& other) const {
    return ptr == other.ptr;
}

template <class T>
bool SingleLinkedList<T>::iterator::operator!=(const iterator& other) const {
    return ptr != other.ptr;
}

// const_iterator
template <class T>
SingleLinkedList<T>::const_iterator::const_iterator(Node* ptr) : ptr {ptr} {}

template <class T>
SingleLinkedList<T>::const_iterator::const_iterator(const iterator& other) : ptr {other.ptr} {}

template <class T>
SingleLinkedList<T>::const_iterator::const_iterator(const const_iterator& other) : ptr {other.ptr} {}

template <class T>
const T& SingleLinkedList<T>::const_iterator::operator*() {
    return ptr->value;
}

template <class T>
const T* SingleLinkedList<T>::const_iterator::operator->() {
    return &(ptr->value);
}

template <class T>
SingleLinkedList<T>::const_iterator& SingleLinkedList<T>::const_iterator::operator++() {
    ptr = ptr->next;
    return *this;
}

template <class T>
SingleLinkedList<T>::const_iterator SingleLinkedList<T>::const_iterator::operator++(int) {
    const_iterator temp {*this};
    ptr = ptr->next;
    return temp;
}

template <class T>
bool SingleLinkedList<T>::const_iterator::operator==(const const_iterator& other) const {
    return ptr == other.ptr;
}

template <class T>
bool SingleLinkedList<T>::const_iterator::operator!=(const const_iterator& other) const {
    return ptr != other.ptr;
}

// SingleLinkedList
template <class T>
SingleLinkedList<T>::SingleLinkedList() : _size {0}, _before_front {new Node({}, nullptr)}, _back {nullptr} {
#ifdef DEBUG
    std::cout << "default constructor was called\n";
#endif
};

template <class T>
SingleLinkedList<T>::SingleLinkedList(std::initializer_list<T> list)
    : _size {0}, _before_front {new Node({}, nullptr)}, _back {nullptr} {
    for (const T& el : list)
        push_back(el);
#ifdef DEBUG
    std::cout << "initializer_list constructor was called\n";
#endif
}

template <class T>
SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList<T>& other)
    : _size {0}, _before_front {new Node({}, nullptr)}, _back {nullptr} {
    for (const T& el : other)
        push_back(el);
#ifdef DEBUG
    std::cout << "copying constructor was called\n";
#endif
}

template <class T>
SingleLinkedList<T>::SingleLinkedList(const std::size_t& size, const T& default_value)
    : _size {0}, _before_front {new Node({}, nullptr)}, _back {nullptr} {
    if (size < 0)
        throw std::length_error("length must be non negative");
    for (std::size_t i {0}; i != size; ++i)
        push_back(default_value);
#ifdef DEBUG
    std::cout << "size constructor was called\n";
#endif
}

template <class T>
SingleLinkedList<T>::SingleLinkedList(SingleLinkedList<T>&& other)
    : _size {other._size}, _before_front {other._before_front}, _back {other._back} {
    other._before_front = new Node({});
    other._back = nullptr;
    other._size = 0;
#ifdef DEBUG
    std::cout << "moving constructor was called\n";
#endif
}

template <class T>
SingleLinkedList<T>::~SingleLinkedList() {
    Node* next;
    while (_before_front) {
        next = _before_front->next;
        delete _before_front;
        _before_front = next;
    }
#ifdef DEBUG
    std::cout << "destructor was called\n";
#endif
}

template <class T>
SingleLinkedList<T>& SingleLinkedList<T>::operator=(const SingleLinkedList<T>& other) {
    _size = 0;
    Node* next;
    while (_before_front->next) {
        next = _before_front->next->next;
        delete _before_front->next;
        _before_front->next = next;
    }
    _back = nullptr;

    for (const T& el : other)
        push_back(el);

    return *this;
}

template <class T>
SingleLinkedList<T>& SingleLinkedList<T>::operator=(SingleLinkedList<T>&& other) {
    Node* next;
    while (_before_front) {
        next = _before_front->next;
        delete _before_front;
        _before_front = next;
    }

    _before_front = other._before_front;
    _back = other._back;
    _size = other._size;

    other._before_front = new Node({});
    other._back = nullptr;
    other._size = 0;
}

template <class T>
T& SingleLinkedList<T>::operator[](std::size_t index) {
    if (index >= _size)
        throw std::out_of_range("list index out of range");

    Node* temp {_before_front->next};
    for (std::size_t i {0}; i != index; ++i)
        temp = temp->next;
    return temp->value;
}

template <class T>
const T& SingleLinkedList<T>::operator[](std::size_t index) const {
    if (index >= _size)
        throw std::out_of_range("list index out of range");

    Node* temp {_before_front->next};
    for (std::size_t i {0}; i != index; ++i)
        temp = temp->next;
    return temp->value;
}

template <class T>
SingleLinkedList<T>::iterator SingleLinkedList<T>::begin() const {
    return iterator(_before_front->next);
}

template <class T>
SingleLinkedList<T>::iterator SingleLinkedList<T>::end() const {
    return iterator(nullptr);
}

template <class T>
SingleLinkedList<T>::iterator SingleLinkedList<T>::before_begin() const {
    return iterator(_before_front);
}
/*
код не работает, т.к. после создания итератора, вызывается деструктор Node,
в результате ссылка становится битой, поэтому лучше создать указатель на начало
template <class T>
SingleLinkedList<T>::iterator SingleLinkedList<T>::before_begin() const {
    Node temp {{}, _front};
    return iterator(&temp);
}
*/

template <class T>
SingleLinkedList<T>::const_iterator SingleLinkedList<T>::cbegin() const {
    return const_iterator(_before_front->next);
}

template <class T>
SingleLinkedList<T>::const_iterator SingleLinkedList<T>::cend() const {
    return const_iterator(nullptr);
}

template <class T>
SingleLinkedList<T>::const_iterator SingleLinkedList<T>::cbefore_begin() const {
    return const_iterator(_before_front);
}

template <class T1>
std::ostream& operator<<(std::ostream& os, const SingleLinkedList<T1>& list) {
    os << '[';
    for (struct SingleLinkedList<T1>::Node* iter {list._before_front->next}; iter != nullptr; iter = iter->next) {
        os << iter->value << ", ";
    }
    if (list._size > 0)
        os << "\b\b";
    return os << ']';
}

template <class T>
std::size_t SingleLinkedList<T>::size() const {
    return _size;
}

template <class T>
bool SingleLinkedList<T>::empty() const {
    return _size == 0;
}

template <class T>
T& SingleLinkedList<T>::front() {
    if (_before_front->next == nullptr)
        throw std::out_of_range("Empty list");
    return _before_front->next->value;
}

template <class T>
T& SingleLinkedList<T>::front() const {
    if (_before_front->next == nullptr)
        throw std::out_of_range("Empty list");
    return _before_front->next->value;
}

template <class T>
T& SingleLinkedList<T>::back() {
    if (_before_front == nullptr)
        throw std::out_of_range("Empty list");
    return _back->value;
}

template <class T>
T& SingleLinkedList<T>::back() const {
    if (_before_front == nullptr)
        throw std::out_of_range("Empty list");
    return _back->value;
}

template <class T>
void SingleLinkedList<T>::push_front(const T& value) {
    _before_front->next = new Node(value, _before_front->next);
    if (_back == nullptr)
        _back = _before_front->next = new Node(value);
    ++_size;
}

template <class T>
void SingleLinkedList<T>::push_back(const T& value) {
    if (_back == nullptr)
        _before_front->next = _back = new Node(value);
    else {
        _back->next = new Node(value);
        _back = _back->next;
    }
    ++_size;
}

template <class T>
void SingleLinkedList<T>::pop_front() {
    if (_before_front->next == nullptr)
        throw std::length_error("Pop from empty list");

    --_size;
    Node* temp {_before_front->next};
    _before_front->next = _before_front->next->next;
    if (_before_front->next == nullptr)
        _back = nullptr;

    delete temp;
}

template <class T>
void SingleLinkedList<T>::pop_back() {
    if (_before_front->next == nullptr)
        throw std::length_error("Pop from empty list");

    --_size;
    Node* temp {_before_front};
    while (temp->next != _back)
        temp = temp->next;

    delete _back;
    _back = temp;
    if (_back == _before_front)
        _back = nullptr;
    else
        _back->next = nullptr;
}

template <class T>
void SingleLinkedList<T>::insert_after(const iterator& it, const T& value) {
    it.ptr->next = new Node(value, it.ptr->next);
    if (it.ptr == _back)
        _back = it.ptr->next;
    ++_size;
}

template <class T>
void SingleLinkedList<T>::insert_after(const const_iterator& it, const T& value) {
    it.ptr->next = new Node(value, it.ptr->next);
    if (it.ptr == _back)
        _back = it.ptr->next;
    ++_size;
}

template <class T>
void SingleLinkedList<T>::erase_after(const iterator& it) {
    Node* temp {it.ptr->next};
    it.ptr->next = it.ptr->next->next;
    delete temp;
    --_size;
}

template <class T>
void SingleLinkedList<T>::erase_after(const const_iterator& it) {
    Node* temp {it.ptr->next};
    it.ptr->next = it.ptr->next->next;
    delete temp;
    --_size;
}

template <class T>
void SingleLinkedList<T>::reverse() {
    if (_size != 0) {
        Node* temp = _before_front->next;
        Node* new_front {new Node(_before_front->next->value)};
        _back = new_front;
        _before_front->next = _before_front->next->next;
        delete temp;

        while (_before_front->next) {
            temp = _before_front->next;
            new_front = new Node(_before_front->next->value, new_front);
            _before_front->next = _before_front->next->next;
            delete temp;
        }

        _before_front->next = new_front;
    }
}
