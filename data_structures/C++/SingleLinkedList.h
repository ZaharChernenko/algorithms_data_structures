#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <ostream>
#include <stdexcept>

template <class T>
class SingleLinkedList {
  protected:
    struct Node {
        T value;
        Node* next;

        Node(const T& value, Node* next = nullptr);
    };

    std::size_t _size;
    Node* _front;
    Node* _back;

  public:
    class iterator;
    class const_iterator;

    class iterator {
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
        using iterator_category = std::output_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

      protected:
        Node* ptr;

      public:
        const_iterator(Node* ptr);
        const_iterator(const iterator& other);
        const_iterator(const const_iterator& other);

        const T& operator*();
        const T* operator->();
        const_iterator& operator++();
        [[nodiscard]] const_iterator operator++(int); // здесь вызывается копирование, поэтому ссылка не нужна
        bool operator==(const const_iterator& other) const;
        bool operator!=(const const_iterator& other) const;
    };

    SingleLinkedList();
    SingleLinkedList(std::initializer_list<T> list);
    ~SingleLinkedList();

    template <class T1> // дружественные функции необходимо объявлять шаблонными у шаблонного класса
    friend std::ostream& operator<<(std::ostream& os, const SingleLinkedList<T1>& list);

    [[nodiscard]] iterator begin() const;
    [[nodiscard]] iterator end() const;
    [[nodiscard]] const_iterator cbegin() const;
    [[nodiscard]] const_iterator cend() const;
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
SingleLinkedList<T>::SingleLinkedList() : _front {nullptr}, _back {nullptr}, _size {0} {};

template <class T>
SingleLinkedList<T>::SingleLinkedList(std::initializer_list<T> list) : _size {0}, _front {nullptr}, _back {nullptr} {
    for (const T el : list)
        push_back(el);
}

template <class T>
SingleLinkedList<T>::~SingleLinkedList() {
    Node* next;
    while (_front) {
        next = _front->next;
        delete _front;
        _front = next;
    }
}

template <class T>
SingleLinkedList<T>::iterator SingleLinkedList<T>::begin() const {
    return iterator(_front);
}

template <class T>
SingleLinkedList<T>::iterator SingleLinkedList<T>::end() const {
    return iterator(nullptr);
}

template <class T>
SingleLinkedList<T>::const_iterator SingleLinkedList<T>::cbegin() const {
    return const_iterator(_front);
}

template <class T>
SingleLinkedList<T>::const_iterator SingleLinkedList<T>::cend() const {
    return const_iterator(nullptr);
}

template <class T1>
std::ostream& operator<<(std::ostream& os, const SingleLinkedList<T1>& list) {
    os << '[';
    for (struct SingleLinkedList<T1>::Node* iter {list._front}; iter != nullptr; iter = iter->next) {
        os << iter->value << ", ";
    }
    if (!list.empty())
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
    if (_front == nullptr)
        throw std::out_of_range("Empty list");
    return _front->value;
}

template <class T>
T& SingleLinkedList<T>::front() const {
    if (_front == nullptr)
        throw std::out_of_range("Empty list");
    return _front->value;
}

template <class T>
T& SingleLinkedList<T>::back() {
    if (_front == nullptr)
        throw std::out_of_range("Empty list");
    return _back->value;
}

template <class T>
T& SingleLinkedList<T>::back() const {
    if (_front == nullptr)
        throw std::out_of_range("Empty list");
    return _back->value;
}

template <class T>
void SingleLinkedList<T>::push_front(const T& value) {
    _front = new Node(value, _front);
    if (_back == nullptr)
        _back = _front;
    ++_size;
}

template <class T>
void SingleLinkedList<T>::push_back(const T& value) {
    if (_back == nullptr)
        _front = _back = new Node(value);
    else {
        _back->next = new Node(value);
        _back = _back->next;
    }
    ++_size;
}

template <class T>
void SingleLinkedList<T>::pop_front() {
    if (_front == nullptr)
        throw std::length_error("Pop from empty list");

    --_size;
    Node* temp {_front};
    _front = _front->next;
    if (_front == nullptr)
        _back = nullptr;

    delete temp;
}

template <class T>
void SingleLinkedList<T>::pop_back() {
    if (_front == nullptr)
        throw std::length_error("Pop from empty list");

    --_size;
    if (_size == 0) {
        delete _back;
        _front = _back = nullptr;
        return;
    }

    Node* temp {_front};
    while (temp->next != _back)
        temp = temp->next;

    delete _back;
    _back = temp;
    _back->next = nullptr;
}
