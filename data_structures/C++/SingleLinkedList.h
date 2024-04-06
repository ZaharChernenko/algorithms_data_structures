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

        Node(T value, Node* next = nullptr);
    };

    std::size_t _size;
    Node* _front;
    Node* _back;

  public:
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

        T& operator*();
        T* operator->();
        iterator& operator++();
        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;
    };

    SingleLinkedList();
    SingleLinkedList(std::initializer_list<T> list);
    ~SingleLinkedList();

    template <class T1> // дружественные функции необходимо объявлять шаблонными у шаблонного класса
    friend std::ostream& operator<<(std::ostream& os, const SingleLinkedList<T1>& list);

    iterator begin();
    iterator end();
    [[nodiscard]] std::size_t size() const;
    [[nodiscard]] bool empty() const;
    T& front();
    T& front() const;
    T& back();
    T& back() const;

    void push_front(T value);
    void push_back(T value);
    void pop_front();
    void pop_back();
};

template <class T> // если не определить то будет warning, что конструктор неопределен
SingleLinkedList<T>::Node::Node(T value, Node* next) : value {value}, next {next} {}

template <class T>
SingleLinkedList<T>::iterator::iterator(Node* ptr) : ptr {ptr} {}

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
bool SingleLinkedList<T>::iterator::operator==(const iterator& other) const {
    return this->ptr == other.ptr;
}

template <class T>
bool SingleLinkedList<T>::iterator::operator!=(const iterator& other) const {
    return this->ptr != other.ptr;
}

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
SingleLinkedList<T>::iterator SingleLinkedList<T>::begin() {
    return iterator(_front);
}

template <class T>
SingleLinkedList<T>::iterator SingleLinkedList<T>::end() {
    return iterator(nullptr);
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
void SingleLinkedList<T>::push_front(T value) {
    _front = new Node(value, _front);
    if (_back == nullptr)
        _back = _front;
    ++_size;
}

template <class T>
void SingleLinkedList<T>::push_back(T value) {
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
