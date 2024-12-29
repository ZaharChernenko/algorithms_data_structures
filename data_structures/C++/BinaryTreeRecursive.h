// AVL-tree
#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <iterator>
#include <ostream>
#include <stack>
#include <type_traits>
#include <utility>
#include <vector>

template <typename DataType, typename Comparator = std::less<DataType>>
class BinaryTreeRecursive {
  protected:
    template <typename IteratorDataType>
    class BasicIterator;

  public:
    using container_type = BinaryTreeRecursive<DataType>;
    using const_reference = const DataType&;
    using value_type = DataType;
    using reference = DataType&;
    using size_type = std::size_t;
    using iterator = BasicIterator<DataType>;
    using const_iterator = BasicIterator<const DataType>;

    BinaryTreeRecursive();
    BinaryTreeRecursive(const BinaryTreeRecursive<DataType, Comparator>& other);
    BinaryTreeRecursive(BinaryTreeRecursive<DataType, Comparator>&& other);
    BinaryTreeRecursive(std::initializer_list<DataType> arr);
    // поскольку рекурсия точно завершится, то переполнения не будет, также память стека и память кучи раздельна,
    // поэтому даже если куча забита, то деструктор должен выполнится без исключений, поэтому отмечаем noexcept
    ~BinaryTreeRecursive() noexcept;

    BinaryTreeRecursive<DataType, Comparator>& operator=(const BinaryTreeRecursive<DataType, Comparator>& other);
    BinaryTreeRecursive<DataType, Comparator>& operator=(BinaryTreeRecursive<DataType, Comparator>&& other);

    operator std::vector<DataType>() const;
    explicit operator bool() const noexcept;

    template <typename DataType1, typename Comparator1>
    friend std::ostream& operator<<(std::ostream& os, const BinaryTreeRecursive<DataType1, Comparator1>& tree);

    // с помощью using можно сократить код, не реализуя два разных класса
    [[nodiscard]] iterator begin() noexcept;
    [[nodiscard]] iterator end() noexcept;
    [[nodiscard]] const_iterator begin() const noexcept;
    [[nodiscard]] const_iterator end() const noexcept;
    [[nodiscard]] const_iterator cbegin() const noexcept;
    [[nodiscard]] const_iterator cend() const noexcept;

    [[nodiscard]] std::size_t size() const noexcept;
    [[nodiscard]] bool empty() const noexcept;

    void insert(const DataType& val);
    void insert(DataType&& val);

    std::size_t erase(const DataType& val);
    iterator erase(iterator it);

    iterator find(const DataType& val) noexcept;
    const_iterator find(const DataType& val) const noexcept;
    bool contains(const DataType& val) const noexcept;

    void swap(BinaryTreeRecursive& other) noexcept;

  protected:
    struct Node {
        Node(const DataType& val);
        Node(DataType&& val);

        Node* left {nullptr};
        Node* right {nullptr};
        DataType val {};
        // высота - количество вершин от текущего узла до самого дальнего
        int8_t height {1};
    };

    template <typename IteratorDataType>
    class BasicIterator {
      protected:
        // обе структуры лежат в <type_traits>
        using MutableIteratorDataType = std::remove_const<IteratorDataType>::type;
        using ConstIteratorDataType = std::add_const<IteratorDataType>::type;

      public:
        // нужен чтобы хранить разность между двумя указателями, без него остальные using'и неработают
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;
        using value_type = IteratorDataType;
        using pointer = IteratorDataType*;
        using reference = IteratorDataType&;
        using const_reference = ConstIteratorDataType&;
        BasicIterator() noexcept = default;
        BasicIterator(const BasicIterator& other) noexcept;
        BasicIterator(BasicIterator&& other) noexcept;
        /*
         SFINAE - Substitution Failure Is Not An Error. При определении перегрузок функции ошибочные инстанциации
         шаблонов не вызывают ошибку компиляции, а отбрасываются из списка кандидатов на наиболее подходящую перегрузку.
         std::is_const - структура, которая содержит поле value, в котором лежит вердикт, является ли тип константным
         или нет а enable_if содержит type только если получает, первым элементом true (вторым элементом может быть
         любой тип)
        */
        template <typename OtherIteratorDataType,
                  typename = typename std::enable_if<!std::is_const<OtherIteratorDataType>::value>::type>
        BasicIterator(const BasicIterator<OtherIteratorDataType>& other);

        template <typename OtherIteratorDataType,
                  typename = typename std::enable_if<!std::is_const<OtherIteratorDataType>::value>::type>
        BasicIterator(BasicIterator<OtherIteratorDataType>&& other);

        BasicIterator& operator=(const BasicIterator& other);
        BasicIterator& operator=(BasicIterator&& other);

        template <typename OtherIteratorDataType>
        typename std::enable_if<!std::is_const<OtherIteratorDataType>::value, BasicIterator>::type&
        operator=(const BasicIterator<OtherIteratorDataType>& other);

        template <typename OtherIteratorDataType>
        typename std::enable_if<!std::is_const<OtherIteratorDataType>::value, BasicIterator>::type&
        operator=(BasicIterator<OtherIteratorDataType>&& other);
        /*
          Если класс не шаблонный, то оператор приведения к своему же типу нельзя сделать, однако для шаблонных
          классов такое возможно, что позволяет приводить тип с одним параметром в тип с другим параметром. В этом коде
          реализован оператор приведения (conversion operator) к итератору на константное значение, что позволяет не
          писать отдельные реализации для итераторов с разной константностью

          explicit operator BasicIterator<ConstIteratorDataType>() const;
          template <typename DataType, typename Comparator>
          template <typename IteratorDataType>
          BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::operator
          BasicIterator<ConstIteratorDataType>() const {
              BasicIterator<ConstIteratorDataType> const_iter;
              const_iter.ptr_stack = ptr_stack;
              return const_iter;
          }
        */
        [[nodiscard]] const IteratorDataType& operator*() noexcept;
        /*
         На самом деле оператор -> работает так: (*it.operator->()).value;
         Сначала вызывается operator->() у итератора, а потом уже к этому указателю применяется оператор стрелка,
         т.е. он работает как бы дважды.
         При обязательно нужно возвращать именно указатель, т.к. в синтаксисе языке -> предназначена именно для такого
         типа данных
        */
        [[nodiscard]] const IteratorDataType* operator->() noexcept;
        BasicIterator& operator++();
        [[nodiscard]] BasicIterator operator++(int);

        [[nodiscard]] bool operator==(const BasicIterator<MutableIteratorDataType>& other) const noexcept;
        [[nodiscard]] bool operator==(const BasicIterator<ConstIteratorDataType>& other) const noexcept;
        [[nodiscard]] bool operator!=(const BasicIterator<MutableIteratorDataType>& other) const noexcept;
        [[nodiscard]] bool operator!=(const BasicIterator<ConstIteratorDataType>& other) const noexcept;

      protected:
        std::stack<Node*> ptr_stack {};
        // не const, потому что ноды могут меняться, а также стека с константами не существует
        explicit BasicIterator(Node* node);

        friend class BinaryTreeRecursive;
    };

    Node* _insert(Node* cur_node, const DataType& val);
    Node* _insert(Node* cur_node, DataType&& val);
    Node* _erase(Node* cur_node, const DataType& val);
    Node* _erase(Node* cur_node, Node* node2delete);
    Node* _find(Node* cur_node, const DataType& val) const noexcept;
    void _printTree(std::ostream& os, const Node* const cur_node, const Node* const leftest_node) const;
    Node* _copyTree(Node* source_node);
    void _deleteTree(Node* cur_node) noexcept;
    Node* _getLeftestNode(Node* cur_node) const;
    Node* _replaceToMin(Node* cur_node, Node*& node_to_replace);
    void _toVector(Node* cur_node, std::size_t& cur_index, std::vector<DataType>& res) const;
    int8_t _getNodeHeight(const Node* cur_node) const;
    void _fixNodeHeight(Node* cur_node);
    // поворот, использующийся в случае если у левого поддерева левое поддерево больше, чем все правое исходного
    // (если равны), то тогда разница |1 + h(node->left->left) - h(node->right)| <= 1, где + 1 - сама левая вершина
    // также называется малый правый поворот
    Node* _LLRotate(Node* cur_node);
    // малый левый поворот
    Node* _RRRotate(Node* cur_node);
    // поворот, использующийся, когда у левого поддерева, правое поддерево больше, чем все правое поддерево исходного
    // дерева, также называется большой правый поворот
    Node* _LRRotate(Node* cur_node);
    Node* _RLRotate(Node* cur_node);
    int8_t _getBalanceFactor(const Node* cur_node) const;
    // после этого высота становится валидной, высота низлежащих узлов валидна еще перед их предком
    Node* _balance(Node* cur_node);

    Node* _root;
    std::size_t _size;
    constexpr static Comparator _comp {};
};

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::BinaryTreeRecursive() : _root {nullptr}, _size {0} {
#ifdef DEBUG
    std::cout << "BinaryTreeRecursive()\n";
#endif
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::BinaryTreeRecursive(std::initializer_list<DataType> arr)
    : _root {nullptr}, _size {0} {
    for (const DataType& val : arr)
        insert(val);

#ifdef DEBUG
    std::cout << "BinaryTreeRecursive(std::initializer_list<DataType> arr)\n";
#endif
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::BinaryTreeRecursive(const BinaryTreeRecursive<DataType, Comparator>& other)
    : _root {nullptr}, _size {other._size} {
    _root = _copyTree(other._root);
#ifdef DEBUG
    std::cout << "BinaryTreeRecursive(const BinaryTreeRecursive<DataType, Comparator>&)\n";
#endif
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::BinaryTreeRecursive(BinaryTreeRecursive<DataType, Comparator>&& other)
    : _root {other._root}, _size {other._size} {
    other._root = nullptr;
    other._size = 0;
#ifdef DEBUG
    std::cout << "BinaryTreeRecursive(const BinaryTreeRecursive<DataType, Comparator>&&)\n";
#endif
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::~BinaryTreeRecursive() noexcept {
    _deleteTree(_root);
#ifdef DEBUG
    std::cout << "~BinaryTreeRecursive()\n";
#endif
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>&
BinaryTreeRecursive<DataType, Comparator>::operator=(const BinaryTreeRecursive<DataType, Comparator>& other) {
    if (this == &other)
        return *this;
    _deleteTree(_root);
    _root = _copyTree(other._root);
    _size = other._size;

    return *this;
#ifdef DEBUG
    std::cout << "operator=(const BinaryTreeRecursive&)\n";
#endif
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>&
BinaryTreeRecursive<DataType, Comparator>::operator=(BinaryTreeRecursive<DataType, Comparator>&& other) {
    _deleteTree(_root);
    _root = other._root;
    _size = other._size;

    other._root = nullptr;
    other._size = 0;

    return *this;
#ifdef DEBUG
    std::cout << "operator=(BinaryTreeRecursive&&)\n";
#endif
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::operator std::vector<DataType>() const {
    std::vector<DataType> res(_size);
    std::size_t cur_index {0};
    _toVector(_root, cur_index, res);
    return res;
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::operator bool() const noexcept {
    return _size != 0;
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::Node::Node(const DataType& val) : val {val} {}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::Node::Node(DataType&& val) : val {std::move(val)} {}

template <typename DataType, typename Comparator>
void BinaryTreeRecursive<DataType, Comparator>::_printTree(std::ostream& os, const Node* const cur_node,
                                                           const Node* const leftest_node) const {
    if (!cur_node)
        return;
    _printTree(os, cur_node->left, leftest_node);
    if (cur_node != leftest_node) [[likely]]
        os << ',' << ' ';
    os << cur_node->val;
    _printTree(os, cur_node->right, leftest_node);
}

template <typename DataType1, typename Comparator1>
std::ostream& operator<<(std::ostream& os, const BinaryTreeRecursive<DataType1, Comparator1>& tree) {
    os << '[';
    tree._printTree(os, tree._root, tree._getLeftestNode(tree._root));
    return os << ']';
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::iterator BinaryTreeRecursive<DataType, Comparator>::begin() noexcept {
    return iterator(_root);
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::iterator BinaryTreeRecursive<DataType, Comparator>::end() noexcept {
    return iterator(nullptr);
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::const_iterator
BinaryTreeRecursive<DataType, Comparator>::begin() const noexcept {
    return const_iterator(_root);
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::const_iterator
BinaryTreeRecursive<DataType, Comparator>::end() const noexcept {
    return const_iterator(nullptr);
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::const_iterator
BinaryTreeRecursive<DataType, Comparator>::cbegin() const noexcept {
    return const_iterator(_root);
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::const_iterator
BinaryTreeRecursive<DataType, Comparator>::cend() const noexcept {
    return const_iterator(nullptr);
}

template <typename DataType, typename Comparator>
template <typename IteratorDataType>
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::BasicIterator(
    const BasicIterator& other) noexcept
    : ptr_stack {other.ptr_stack} {}

template <typename DataType, typename Comparator>
template <typename IteratorDataType>
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::BasicIterator(
    BasicIterator&& other) noexcept
    : ptr_stack {std::move(other.ptr_stack)} {}

template <typename DataType, typename Comparator>
template <typename IteratorDataType>
template <typename OtherIteratorDataType, typename>
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::BasicIterator(
    const BasicIterator<OtherIteratorDataType>& other)
    : ptr_stack {other.ptr_stack} {}

template <typename DataType, typename Comparator>
template <typename IteratorDataType>
template <typename OtherIteratorDataType, typename>
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::BasicIterator(
    BasicIterator<OtherIteratorDataType>&& other)
    : ptr_stack {std::move(other.ptr_stack)} {}

template <typename DataType, typename Comparator>
template <typename IteratorDataType>
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::BasicIterator(Node* node) : ptr_stack {} {
    if (!node)
        return;

    ptr_stack.push(node);
    while ((node = node->left))
        ptr_stack.push(node);
}

template <typename DataType, typename Comparator>
template <typename IteratorDataType>
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>&
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::operator=(const BasicIterator& other) {
    ptr_stack = other.ptr_stack;
    return *this;
}

template <typename DataType, typename Comparator>
template <typename IteratorDataType>
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>&
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::operator=(BasicIterator&& other) {
    ptr_stack = std::move(other.ptr_stack);
    return *this;
}

template <typename DataType, typename Comparator>
template <typename IteratorDataType>
template <typename OtherIteratorDataType>
typename std::enable_if<
    !std::is_const<OtherIteratorDataType>::value,
    typename BinaryTreeRecursive<DataType, Comparator>::template BasicIterator<IteratorDataType>>::type&
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::operator=(
    const BasicIterator<OtherIteratorDataType>& other) {
    ptr_stack = other.ptr_stack;
    return *this;
}

template <typename DataType, typename Comparator>
template <typename IteratorDataType>
template <typename OtherIteratorDataType>
// template ниже нужен, чтобы BasicIterator воспринимался, как шаблон
typename std::enable_if<
    !std::is_const<OtherIteratorDataType>::value,
    typename BinaryTreeRecursive<DataType, Comparator>::template BasicIterator<IteratorDataType>>::type&
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::operator=(
    BasicIterator<OtherIteratorDataType>&& other) {
    ptr_stack = std::move(other.ptr_stack);
    return *this;
}

template <typename DataType, typename Comparator>
template <typename IteratorDataType>
const IteratorDataType&
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::operator*() noexcept {
    return ptr_stack.top()->val;
}

template <typename DataType, typename Comparator>
template <typename IteratorDataType>
const IteratorDataType*
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::operator->() noexcept {
    return &(ptr_stack.top()->val);
}

template <typename DataType, typename Comparator>
template <typename IteratorDataType>
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>&
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::operator++() {
    Node* cur_node {ptr_stack.top()};
    ptr_stack.pop();

    Node* right_node {cur_node->right};
    while (right_node) {
        ptr_stack.push(right_node);
        right_node = right_node->left;
    }

    return *this;
}

template <typename DataType, typename Comparator>
template <typename IteratorDataType>
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::operator++(int) {
    BasicIterator cur_iter {*this};
    Node* cur_node {ptr_stack.top()};
    ptr_stack.pop();

    Node* right_node {cur_node->right};
    while (right_node) {
        ptr_stack.push(right_node);
        right_node = right_node->left;
    }

    return cur_iter;
}

template <typename DataType, typename Comparator>
template <typename IteratorDataType>
bool BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::operator==(
    const BasicIterator<MutableIteratorDataType>& other) const noexcept {
    return (ptr_stack.size() == other.ptr_stack.size()) &&
           (!ptr_stack.size() || ptr_stack.top() == other.ptr_stack.top());
}

template <typename DataType, typename Comparator>
template <typename IteratorDataType>
bool BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::operator==(
    const BasicIterator<ConstIteratorDataType>& other) const noexcept {
    return (ptr_stack.size() == other.ptr_stack.size()) &&
           (!ptr_stack.size() || ptr_stack.top() == other.ptr_stack.top());
}

template <typename DataType, typename Comparator>
template <typename IteratorDataType>
bool BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::operator!=(
    const BasicIterator<MutableIteratorDataType>& other) const noexcept {
    return (ptr_stack.size() != other.ptr_stack.size()) ||
           (!ptr_stack.empty() && ptr_stack.top() != other.ptr_stack.top());
}

template <typename DataType, typename Comparator>
template <typename IteratorDataType>
bool BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::operator!=(
    const BasicIterator<ConstIteratorDataType>& other) const noexcept {
    return (ptr_stack.size() != other.ptr_stack.size()) ||
           (!ptr_stack.empty() && ptr_stack.top() != other.ptr_stack.top());
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::Node*
BinaryTreeRecursive<DataType, Comparator>::_copyTree(Node* source_node) {
    if (!source_node)
        return nullptr;

    Node* dest_node = new Node(source_node->val);
    dest_node->left = _copyTree(source_node->left);
    dest_node->right = _copyTree(source_node->right);

    return dest_node;
}

template <typename DataType, typename Comparator>
void BinaryTreeRecursive<DataType, Comparator>::_deleteTree(Node* cur_node) noexcept {
    if (!cur_node)
        return;
    _deleteTree(cur_node->left);
    _deleteTree(cur_node->right);
    delete cur_node;
}

template <typename DataType, typename Comparator>
std::size_t BinaryTreeRecursive<DataType, Comparator>::size() const noexcept {
    return _size;
}

template <typename DataType, typename Comparator>
bool BinaryTreeRecursive<DataType, Comparator>::empty() const noexcept {
    return _size == 0;
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::Node*
BinaryTreeRecursive<DataType, Comparator>::_insert(Node* cur_node, const DataType& val) {
    if (!cur_node) {
        ++_size;
        return new Node(val);
    }

    if (_comp(val, cur_node->val))
        cur_node->left = _insert(cur_node->left, val);
    else if (val != cur_node->val)
        cur_node->right = _insert(cur_node->right, val);

    return _balance(cur_node);
}

template <typename DataType, typename Comparator>
void BinaryTreeRecursive<DataType, Comparator>::insert(const DataType& val) {
    _root = _insert(_root, val);
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::Node* BinaryTreeRecursive<DataType, Comparator>::_insert(Node* cur_node,
                                                                                                    DataType&& val) {
    if (!cur_node) {
        ++_size;
        return new Node(std::move(val));
    }

    if (_comp(val, cur_node->val))
        cur_node->left = _insert(cur_node->left, std::move(val));
    else if (val != cur_node->val)
        cur_node->right = _insert(cur_node->right, std::move(val));

    return _balance(cur_node);
}

template <typename DataType, typename Comparator>
void BinaryTreeRecursive<DataType, Comparator>::insert(DataType&& val) {
    _root = _insert(_root, std::move(val));
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::Node*
BinaryTreeRecursive<DataType, Comparator>::_getLeftestNode(Node* node) const {
    if (!node) [[unlikely]]
        return nullptr;

    Node* left_node {node->left};
    while (left_node) {
        node = left_node;
        left_node = left_node->left;
    }

    return node;
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::Node*
BinaryTreeRecursive<DataType, Comparator>::_replaceToMin(Node* cur_node, Node*& node_to_replace) {
    if (!cur_node->left) {
        node_to_replace = cur_node;
        return cur_node->right;
    }
    cur_node->left = _replaceToMin(cur_node->left, node_to_replace);
    return _balance(cur_node);
}

template <typename DataType, typename Comparator>
std::size_t BinaryTreeRecursive<DataType, Comparator>::erase(const DataType& val) {
    std::size_t size_before_erase {_size};
    _root = _erase(_root, val);
    return size_before_erase - _size;
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::iterator BinaryTreeRecursive<DataType, Comparator>::erase(iterator it) {
    Node* node2delete {it.ptr_stack.top()};
    BasicIterator new_it {it};
    ++new_it;
    _root = _erase(_root, node2delete);

    return new_it;
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::iterator
BinaryTreeRecursive<DataType, Comparator>::find(const DataType& val) noexcept {
    return iterator(_find(_root, val));
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::const_iterator
BinaryTreeRecursive<DataType, Comparator>::find(const DataType& val) const noexcept {
    return const_iterator(_find(_root, val));
}

template <typename DataType, typename Comparator>
bool BinaryTreeRecursive<DataType, Comparator>::contains(const DataType& val) const noexcept {
    return _find(_root, val) != nullptr;
}

template <typename DataType, typename Comparator>
void BinaryTreeRecursive<DataType, Comparator>::swap(BinaryTreeRecursive& other) noexcept {
    std::swap(_root, other._root);
    std::swap(_size, other._size);
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::Node*
BinaryTreeRecursive<DataType, Comparator>::_erase(Node* cur_node, const DataType& val) {
    if (!cur_node)
        return cur_node;

    if (_comp(val, cur_node->val))
        cur_node->left = _erase(cur_node->left, val);
    else if (val != cur_node->val)
        cur_node->right = _erase(cur_node->right, val);
    else {
        Node* left {cur_node->left};
        Node* right {cur_node->right};
        delete cur_node;
        if (left && right) {
            right = _replaceToMin(right, cur_node);
            cur_node->left = left;
            cur_node->right = right;
        } else
            cur_node = !left ? right : left;
        --_size;
    }

    return !cur_node ? cur_node : _balance(cur_node);
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::Node* BinaryTreeRecursive<DataType, Comparator>::_erase(Node* cur_node,
                                                                                                   Node* node2delete) {
    if (!cur_node)
        return cur_node;

    if (_comp(node2delete->val, cur_node->val))
        cur_node->left = _erase(cur_node->left, node2delete);
    else if (node2delete->val != cur_node->val)
        cur_node->right = _erase(cur_node->right, node2delete);
    else {
        Node* left {cur_node->left};
        Node* right {cur_node->right};
        delete cur_node;
        if (left && right) {
            right = _replaceToMin(right, cur_node);
            cur_node->left = left;
            cur_node->right = right;
        } else
            cur_node = !left ? right : left;
        --_size;
    }

    return !cur_node ? cur_node : _balance(cur_node);
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::Node*
BinaryTreeRecursive<DataType, Comparator>::_find(Node* cur_node, const DataType& val) const noexcept {
    if (!cur_node)
        return nullptr;
    if (cur_node->val == val)
        return cur_node;
    if (_comp(val, cur_node->val))
        return _find(cur_node->left, val);
    return _find(cur_node->right, val);
}

template <typename DataType, typename Comparator>
void BinaryTreeRecursive<DataType, Comparator>::_toVector(Node* cur_node, std::size_t& cur_index,
                                                          std::vector<DataType>& res) const {
    if (!cur_node)
        return;
    _toVector(cur_node->left, cur_index, res);
    res[cur_index++] = cur_node->val;
    _toVector(cur_node->right, cur_index, res);
}

template <typename DataType, typename Comparator>
int8_t BinaryTreeRecursive<DataType, Comparator>::_getNodeHeight(const Node* cur_node) const {
    if (!cur_node)
        return 0;
    return cur_node->height;
}

template <typename DataType, typename Comparator>
void BinaryTreeRecursive<DataType, Comparator>::_fixNodeHeight(Node* cur_node) {
    cur_node->height = std::max(_getNodeHeight(cur_node->left), _getNodeHeight(cur_node->right)) + 1;
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::Node* BinaryTreeRecursive<DataType, Comparator>::_LLRotate(Node* cur_node) {
    Node* left {cur_node->left};
    cur_node->left = left->right;
    left->right = cur_node;
    _fixNodeHeight(cur_node);
    _fixNodeHeight(left);
    return left;
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::Node* BinaryTreeRecursive<DataType, Comparator>::_RRRotate(Node* cur_node) {
    Node* right {cur_node->right};
    cur_node->right = right->left;
    right->left = cur_node;
    _fixNodeHeight(cur_node);
    _fixNodeHeight(right);
    return right;
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::Node* BinaryTreeRecursive<DataType, Comparator>::_LRRotate(Node* cur_node) {
    cur_node->left = _RRRotate(cur_node->left);
    return _LLRotate(cur_node);
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::Node* BinaryTreeRecursive<DataType, Comparator>::_RLRotate(Node* cur_node) {
    cur_node->right = _LLRotate(cur_node->right);
    return _RRRotate(cur_node);
}

template <typename DataType, typename Comparator>
int8_t BinaryTreeRecursive<DataType, Comparator>::_getBalanceFactor(const Node* cur_node) const {
    return _getNodeHeight(cur_node->right) - _getNodeHeight(cur_node->left);
}

template <typename DataType, typename Comparator>
BinaryTreeRecursive<DataType, Comparator>::Node* BinaryTreeRecursive<DataType, Comparator>::_balance(Node* cur_node) {
    // без этого вызова ноды, у которых появился 1 лист не увеличат свою высоту, т.к. ни один поворот не будет вызван
    _fixNodeHeight(cur_node);
    int8_t balance_factor {_getBalanceFactor(cur_node)};

    // перекос вправо
    if (balance_factor == 2) {
        // правое поддерево правого поддерева больше
        if (_getBalanceFactor(cur_node->right) == 1)
            return _RRRotate(cur_node);
        return _RLRotate(cur_node);
    } else if (balance_factor == -2) {
        if (_getBalanceFactor(cur_node->left) == -1)
            return _LLRotate(cur_node);
        return _LRRotate(cur_node);
    }

    return cur_node;
}
