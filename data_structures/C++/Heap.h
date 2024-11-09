#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <utility>
#include <vector>

// #define DEBUG

#ifdef DEBUG
#include <iostream>
#endif

namespace {
template <class Container, class Comparator>
inline void siftDown(Container& container, std::size_t index, std::size_t size) {
    static Comparator comp {};
    std::size_t child_1, child_2;

    while ((child_1 = index * 2 + 1) < size) {
        std::size_t limit_index = child_1;
        if (child_2 = child_1 + 1; child_2 != size && comp(container[child_2], container[child_1]))
            limit_index = child_2;
        if (comp(container[index], container[limit_index]))
            break;

        std::swap(container[index], container[limit_index]);
        index = limit_index;
    }
}
} // namespace

template <class Container, class Comparator>
void heapify(Container& container) {
    std::size_t size {container.size()};
    // т.к. вершин, которые удалены от листьев n / 2, то начинаем с n / 2 - 1 индекса
    for (std::size_t i {size / 2 - 1}; i != std::numeric_limits<std::size_t>::max(); --i) {
        siftDown<Container, Comparator>(container, i, size);
    }
}

template <class T>
void heapSort(std::vector<T>& arr) {
    heapify<std::vector<T>, std::greater<T>>(arr);
    std::size_t heap_size {arr.size()};

    for (std::size_t bypass {0}; bypass + 1 < arr.size(); ++bypass) {
        std::swap(arr[0], arr[--heap_size]); // теперь первый элемент будет последним
        siftDown<std::vector<T>, std::greater<T>>(arr, 0, heap_size); // поддерживаем свойство кучи
    }
}

template <class DataType, class Comparator = std::less<DataType>>
class Heap {
    // https://en.cppreference.com/w/cpp/named_req
    using container_type = std::vector<DataType>;
    using value_type = container_type::value_type;
    using reference = container_type::reference;
    using const_reference = container_type::const_reference;
    using size_type = container_type::size_type;

  public:
    Heap();
    Heap(std::size_t size);
    Heap(std::size_t size, const DataType& val);
    Heap(std::initializer_list<DataType> list);
    // можно опустить шаблонные аргументы, компилятор самостоятельно догадается
    Heap(const Heap& other);
    Heap(Heap<DataType, Comparator>&& other);
    ~Heap() = default;

  public:
    Heap<DataType, Comparator>& operator=(const Heap<DataType, Comparator>& other);
    Heap<DataType, Comparator>& operator=(Heap<DataType, Comparator>&& other);
    explicit operator bool() const;

    template <class DataType1, class Comparator1>
    friend std::ostream& operator<<(std::ostream& os, const Heap<DataType1, Comparator1>& heap);

    void push(const DataType& val);
    void pop();
    [[nodiscard]] std::size_t size() const;
    [[nodiscard]] bool empty() const;
    [[nodiscard]] const DataType& top() const;

  protected:
    inline void siftUp(std::size_t index);
    inline void siftDown(std::size_t index);

  protected:
    std::vector<DataType> _data;
    std::size_t _size;
    constexpr static Comparator _comp {};
};

// constructors
template <class DataType, class Comparator>
Heap<DataType, Comparator>::Heap() : _data {}, _size {0} {
#ifdef DEBUG
    std::cout << "Heap()\n";
#endif
}

template <class DataType, class Comparator>
Heap<DataType, Comparator>::Heap(std::size_t size) : _data(size), _size {size} {
#ifdef DEBUG
    std::cout << "Heap(std::size_t)\n";
#endif
}

template <class DataType, class Comparator>
Heap<DataType, Comparator>::Heap(std::size_t size, const DataType& val) : _data(size, val), _size {size} {
#ifdef DEBUG
    std::cout << "Heap(std::size_t, const DataType&)\n";
#endif
}

template <class DataType, class Comparator>
Heap<DataType, Comparator>::Heap(std::initializer_list<DataType> list)
    : _data(list.begin(), list.end()), _size {list.size()} {
    heapify<std::vector<DataType>, Comparator>(_data);
}

template <class DataType, class Comparator>
Heap<DataType, Comparator>::Heap(const Heap& other) : _data {other._data}, _size {other._size} {
#ifdef DEBUG
    std::cout << "Heap(const Heap& other)\n";
#endif
}

template <class DataType, class Comparator>
Heap<DataType, Comparator>::Heap(Heap<DataType, Comparator>&& other)
    : _data {std::move(other._data)}, _size {other._size} {
    other._size = 0; // moving constructor is useless for built-in types
#ifdef DEBUG
    std::cout << "Heap(Heap&& other)\n";
#endif
}

template <class DataType, class Comparator>
Heap<DataType, Comparator>& Heap<DataType, Comparator>::operator=(const Heap<DataType, Comparator>& other) {
#ifdef DEBUG
    std::cout << "operator=(const Heap& other)\n";
#endif
    _size = other._size;
    _data = other._data;
    return *this;
}

template <class DataType, class Comparator>
Heap<DataType, Comparator>& Heap<DataType, Comparator>::operator=(Heap<DataType, Comparator>&& other) {
#ifdef DEBUG
    std::cout << "operator=(Heap&& other)\n";
#endif
    _size = other._size;
    _data = std::move(other._data);
    other._size = 0;
    return *this;
}

template <class DataType, class Comparator>
Heap<DataType, Comparator>::operator bool() const {
    return _size != 0;
}

template <class DataType1, class Comparator1>
std::ostream& operator<<(std::ostream& os, const Heap<DataType1, Comparator1>& heap) {
    os << '[';
    if (heap.empty())
        return os << ']';
    // без typename компилятор посчитает std::vector<DataType1>::const_iterator за статический член класса
    // typename является указанием для компилятора, что неизвестный идентификатор является типом
    typename std::vector<DataType1>::const_iterator start {heap._data.cbegin()};
    os << *(start++);
    for (; start != heap._data.cend(); ++start)
        os << ',' << ' ' << *start;
    return os << ']';
}

template <class DataType, class Comparator>
void Heap<DataType, Comparator>::siftUp(std::size_t index) {
    std::size_t parent;
    while (index != 0 && _comp(_data[index], _data[parent = (index - 1) / 2])) {
        std::swap(_data[index], _data[parent]);
        index = parent;
    }
}

template <class DataType, class Comparator>
void Heap<DataType, Comparator>::siftDown(std::size_t index) {
    std::size_t child_1, child_2;
    while ((child_1 = index * 2 + 1) < _size) {
        std::size_t limit_index = child_1;
        if (child_2 = child_1 + 1; child_2 != _size && _comp(_data[child_2], _data[child_1])) {
            limit_index = child_2;
        }
        if (_comp(_data[index], _data[limit_index]))
            break;
        std::swap(_data[index], _data[limit_index]);
        index = limit_index;
    }
}

template <class DataType, class Comparator>
void Heap<DataType, Comparator>::push(const DataType& val) {
    _data.push_back(val);
    siftUp(_size++);
}

template <class DataType, class Comparator>
void Heap<DataType, Comparator>::pop() {
    if (!_size) [[unlikely]]
        throw std::length_error("Pop from empty heap");
    std::swap(_data[0], _data[--_size]);
    _data.pop_back();
    siftDown(0);
}

template <class DataType, class Comparator>
std::size_t Heap<DataType, Comparator>::size() const {
    return _size;
}

template <class DataType, class Comparator>
bool Heap<DataType, Comparator>::empty() const {
    return _size == 0;
}

template <class DataType, class Comparator>
const DataType& Heap<DataType, Comparator>::top() const {
    if (_size == 0) [[unlikely]]
        throw std::out_of_range("Empty heap");
    return _data[0];
}
