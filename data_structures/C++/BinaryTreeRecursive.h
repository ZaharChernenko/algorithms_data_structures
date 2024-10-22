#pragma once

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <ostream>
#include <stack>
#include <type_traits>
#include <utility>
#include <vector>

template <class DataType, class Comparator = std::less<DataType>>
class BinaryTreeRecursive {
  protected:
    template <class IteratorDataType>
    class BasicIterator;

  public:
    BinaryTreeRecursive();
    BinaryTreeRecursive(const BinaryTreeRecursive<DataType, Comparator>& other);
    BinaryTreeRecursive(BinaryTreeRecursive<DataType, Comparator>&& other);
    BinaryTreeRecursive(std::initializer_list<DataType> arr);
    ~BinaryTreeRecursive() noexcept;

    BinaryTreeRecursive<DataType, Comparator>& operator=(const BinaryTreeRecursive<DataType, Comparator>& other);
    BinaryTreeRecursive<DataType, Comparator>& operator=(BinaryTreeRecursive<DataType, Comparator>&& other);
    operator std::vector<DataType>() const;

    template <class DataType1, class Comparator1>
    friend std::ostream& operator<<(std::ostream& os, const BinaryTreeRecursive<DataType1, Comparator1>& tree);

    using iterator = BasicIterator<DataType>;
    using const_iterator = BasicIterator<const DataType>;
    [[nodiscard]] iterator begin() const noexcept;
    [[nodiscard]] iterator end() const noexcept;
    [[nodiscard]] const_iterator cbegin() const noexcept;
    [[nodiscard]] const_iterator cend() const noexcept;

    [[nodiscard]] std::size_t size() const noexcept;

    void insert(const DataType& val);
    void insert(DataType&& val);

    std::size_t erase(const DataType& val);
    const_iterator erase(const_iterator it);

  protected:
    struct Node {
        Node(const DataType& val);
        Node(DataType&& val);

        DataType val {};
        Node* left {nullptr};
        Node* right {nullptr};
    };

    template <class IteratorDataType>
    class BasicIterator {
        using MutableIteratorDataType = std::remove_const<IteratorDataType>::type;
        using ConstIteratorDataType = std::add_const<IteratorDataType>::type;

      public:
        BasicIterator() = default;
        BasicIterator(const BasicIterator& other);
        BasicIterator(BasicIterator&& other);

        BasicIterator& operator=(const BasicIterator& other);
        BasicIterator& operator=(BasicIterator&& other);
        operator BasicIterator<ConstIteratorDataType>() const;

        [[nodiscard]] const IteratorDataType& operator*() noexcept;
        [[nodiscard]] const IteratorDataType* operator->() noexcept;
        BasicIterator& operator++();
        [[nodiscard]] BasicIterator operator++(int);

        [[nodiscard]] bool operator==(const BasicIterator<MutableIteratorDataType>& other) const noexcept;
        [[nodiscard]] bool operator==(const BasicIterator<ConstIteratorDataType>& other) const noexcept;
        [[nodiscard]] bool operator!=(const BasicIterator<MutableIteratorDataType>& other) const noexcept;
        [[nodiscard]] bool operator!=(const BasicIterator<ConstIteratorDataType>& other) const noexcept;

        using iterator_category = std::forward_iterator_tag;
        using value_type = IteratorDataType;
        using pointer = IteratorDataType*;
        using reference = IteratorDataType&;
        using const_reference = ConstIteratorDataType&;

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
    void _printTree(std::ostream& os, const Node* const cur_node, const Node* const leftest_node) const;
    Node* _copyTree(Node* source_node);
    void _deleteTree(Node* cur_node) noexcept;
    Node* _getLeftestNode(Node* cur_node) const;
    void _replaceChild(Node* parent, Node* old_child, Node* new_child) noexcept;
    void _toVector(Node* cur_node, std::size_t& cur_index, std::vector<DataType>& res) const;

    Node* _root;
    std::size_t _size;
    constexpr static Comparator _comp {};
};

template <class DataType, class Comparator>
BinaryTreeRecursive<DataType, Comparator>::BinaryTreeRecursive() : _root {nullptr}, _size {0} {
#ifdef DEBUG
    std::cout << "BinaryTreeRecursive()\n";
#endif
}

template <class DataType, class Comparator>
BinaryTreeRecursive<DataType, Comparator>::BinaryTreeRecursive(std::initializer_list<DataType> arr)
    : _root {nullptr}, _size {0} {
    for (const DataType& val : arr)
        insert(val);

#ifdef DEBUG
    std::cout << "BinaryTreeRecursive(std::initializer_list<DataType> arr)\n";
#endif
}

template <class DataType, class Comparator>
BinaryTreeRecursive<DataType, Comparator>::BinaryTreeRecursive(const BinaryTreeRecursive<DataType, Comparator>& other)
    : _root {nullptr}, _size {other._size} {
    _root = _copyTree(other._root);
#ifdef DEBUG
    std::cout << "BinaryTreeRecursive(const BinaryTreeRecursive<DataType, Comparator>&)\n";
#endif
}

template <class DataType, class Comparator>
BinaryTreeRecursive<DataType, Comparator>::BinaryTreeRecursive(BinaryTreeRecursive<DataType, Comparator>&& other)
    : _root {other._root}, _size {other._size} {
    other._root = nullptr;
    other._size = 0;
#ifdef DEBUG
    std::cout << "BinaryTreeRecursive(const BinaryTreeRecursive<DataType, Comparator>&&)\n";
#endif
}

template <class DataType, class Comparator>
BinaryTreeRecursive<DataType, Comparator>::~BinaryTreeRecursive() noexcept {
    _deleteTree(_root);
#ifdef DEBUG
    std::cout << "~BinaryTreeRecursive()\n";
#endif
}

template <class DataType, class Comparator>
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

template <class DataType, class Comparator>
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

template <class DataType, class Comparator>
BinaryTreeRecursive<DataType, Comparator>::operator std::vector<DataType>() const {
    std::vector<DataType> res(_size);
    std::size_t cur_index {0};
    _toVector(_root, cur_index, res);
    return res;
}

template <class DataType, class Comparator>
BinaryTreeRecursive<DataType, Comparator>::Node::Node(const DataType& val) : val {val} {}

template <class DataType, class Comparator>
BinaryTreeRecursive<DataType, Comparator>::Node::Node(DataType&& val) : val {std::move(val)} {}

template <class DataType, class Comparator>
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

template <class DataType1, class Comparator1>
std::ostream& operator<<(std::ostream& os, const BinaryTreeRecursive<DataType1, Comparator1>& tree) {
    os << '[';
    tree._printTree(os, tree._root, tree._getLeftestNode(tree._root));
    return os << ']';
}

template <class DataType, class Comparator>
BinaryTreeRecursive<DataType, Comparator>::iterator BinaryTreeRecursive<DataType, Comparator>::begin() const noexcept {
    return iterator(_root);
}

template <class DataType, class Comparator>
BinaryTreeRecursive<DataType, Comparator>::iterator BinaryTreeRecursive<DataType, Comparator>::end() const noexcept {
    return iterator(nullptr);
}

template <class DataType, class Comparator>
BinaryTreeRecursive<DataType, Comparator>::const_iterator
BinaryTreeRecursive<DataType, Comparator>::cbegin() const noexcept {
    return const_iterator(_root);
}

template <class DataType, class Comparator>
BinaryTreeRecursive<DataType, Comparator>::const_iterator
BinaryTreeRecursive<DataType, Comparator>::cend() const noexcept {
    return const_iterator(nullptr);
}

template <class DataType, class Comparator>
template <class IteratorDataType>
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::BasicIterator(const BasicIterator& other)
    : ptr_stack {other.ptr_stack} {}

template <class DataType, class Comparator>
template <class IteratorDataType>
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::BasicIterator(BasicIterator&& other)
    : ptr_stack {std::move(other.ptr_stack)} {}

template <class DataType, class Comparator>
template <class IteratorDataType>
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::BasicIterator(Node* node) : ptr_stack {} {
    if (!node)
        return;

    ptr_stack.push(node);
    while ((node = node->left))
        ptr_stack.push(node);
}

template <class DataType, class Comparator>
template <class IteratorDataType>
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>&
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::operator=(const BasicIterator& other) {
    ptr_stack = other.ptr_stack;
    return *this;
}

template <class DataType, class Comparator>
template <class IteratorDataType>
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>&
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::operator=(BasicIterator&& other) {
    ptr_stack = std::move(other.ptr_stack);
    return *this;
}

template <class DataType, class Comparator>
template <class IteratorDataType>
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::operator BasicIterator<
    ConstIteratorDataType>() const {
    BasicIterator<ConstIteratorDataType> const_iter;
    const_iter.ptr_stack = ptr_stack;
    return const_iter;
}

template <class DataType, class Comparator>
template <class IteratorDataType>
const IteratorDataType&
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::operator*() noexcept {
    return ptr_stack.top()->val;
}

template <class DataType, class Comparator>
template <class IteratorDataType>
const IteratorDataType*
BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::operator->() noexcept {
    return &(ptr_stack.top()->val);
}

template <class DataType, class Comparator>
template <class IteratorDataType>
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

template <class DataType, class Comparator>
template <class IteratorDataType>
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

template <class DataType, class Comparator>
template <class IteratorDataType>
bool BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::operator==(
    const BasicIterator<MutableIteratorDataType>& other) const noexcept {
    return (ptr_stack.size() == other.ptr_stack.size()) && (ptr_stack.top() == other.ptr_stack.top());
}

template <class DataType, class Comparator>
template <class IteratorDataType>
bool BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::operator==(
    const BasicIterator<ConstIteratorDataType>& other) const noexcept {
    return (ptr_stack.size() == other.ptr_stack.size()) && (ptr_stack.top() == other.ptr_stack.top());
}

template <class DataType, class Comparator>
template <class IteratorDataType>
bool BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::operator!=(
    const BasicIterator<MutableIteratorDataType>& other) const noexcept {
    return (ptr_stack.size() != other.ptr_stack.size()) ||
           (!ptr_stack.empty() && ptr_stack.top() != other.ptr_stack.top());
}

template <class DataType, class Comparator>
template <class IteratorDataType>
bool BinaryTreeRecursive<DataType, Comparator>::BasicIterator<IteratorDataType>::operator!=(
    const BasicIterator<ConstIteratorDataType>& other) const noexcept {
    return (ptr_stack.size() != other.ptr_stack.size()) ||
           (!ptr_stack.empty() && ptr_stack.top() != other.ptr_stack.top());
}

template <class DataType, class Comparator>
BinaryTreeRecursive<DataType, Comparator>::Node*
BinaryTreeRecursive<DataType, Comparator>::_copyTree(Node* source_node) {
    if (!source_node)
        return nullptr;

    Node* dest_node = new Node(source_node->val);
    dest_node->left = _copyTree(source_node->left);
    dest_node->right = _copyTree(source_node->right);

    return dest_node;
}

template <class DataType, class Comparator>
void BinaryTreeRecursive<DataType, Comparator>::_deleteTree(Node* cur_node) noexcept {
    if (!cur_node)
        return;
    _deleteTree(cur_node->left);
    _deleteTree(cur_node->right);
    delete cur_node;
}

template <class DataType, class Comparator>
std::size_t BinaryTreeRecursive<DataType, Comparator>::size() const noexcept {
    return _size;
}

template <class DataType, class Comparator>
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

    return cur_node;
}

template <class DataType, class Comparator>
void BinaryTreeRecursive<DataType, Comparator>::insert(const DataType& val) {
    _root = _insert(_root, val);
}

template <class DataType, class Comparator>
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

    return cur_node;
}

template <class DataType, class Comparator>
void BinaryTreeRecursive<DataType, Comparator>::insert(DataType&& val) {
    _root = _insert(_root, std::move(val));
}

template <class DataType, class Comparator>
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

template <class DataType, class Comparator>
BinaryTreeRecursive<DataType, Comparator>::Node*
BinaryTreeRecursive<DataType, Comparator>::_erase(Node* cur_node, const DataType& val) {
    if (!cur_node)
        return cur_node;

    if (_comp(val, cur_node->val))
        cur_node->left = _erase(cur_node->left, val);
    else if (val != cur_node->val)
        cur_node->right = _erase(cur_node->right, val);
    else {
        if (cur_node->left && cur_node->right) {
            Node* parent {cur_node};
            Node* child {cur_node->right};

            while (child->left) {
                parent = child;
                child = child->left;
            }
            std::swap(child, cur_node);
            cur_node->left = child->left;
            if (child->right != cur_node) {
                cur_node->right = child->right;
                _replaceChild(parent, cur_node, nullptr);
            }
            delete child;
        } else {
            Node* temp {cur_node};
            if (cur_node->left)
                cur_node = cur_node->left;
            else
                cur_node = cur_node->right;
            delete temp;
        }
        --_size;
    }

    return cur_node;
}

template <class DataType, class Comparator>
std::size_t BinaryTreeRecursive<DataType, Comparator>::erase(const DataType& val) {
    std::size_t size_before_erase {_size};
    _root = _erase(_root, val);
    return size_before_erase - _size;
}

template <class DataType, class Comparator>
BinaryTreeRecursive<DataType, Comparator>::Node* BinaryTreeRecursive<DataType, Comparator>::_erase(Node* cur_node,
                                                                                                   Node* node2delete) {
    if (!cur_node)
        return cur_node;

    if (_comp(node2delete->val, cur_node->val))
        cur_node->left = _erase(cur_node->left, node2delete);
    else if (node2delete->val != cur_node->val)
        cur_node->right = _erase(cur_node->right, node2delete);
    else {
        if (cur_node->left && cur_node->right) {
            Node* parent {cur_node};
            // child - самое маленькое значение справа
            Node* child {cur_node->right};

            while (child->left) {
                parent = child;
                child = child->left;
            }

            // child и cur_node - сами по себе содержат адреса, и нам необходимо удалить адрес именно cur_node,
            // поэтому мы достаем child и меняем местами адреса, на которые они указывают
            std::swap(child, cur_node);
            // теперь cur_node указывает на child, поэтому нам нужно забрать левый указатель
            cur_node->left = child->left;
            // в случае, если изначально cur_node->right указывал на child, то нам не нужно переназначать right,
            // т.к. будет циклическая ссылка, а должно быть nullptr
            if (child->right != cur_node) {
                cur_node->right = child->right;
                // несмотря на то, что мы поменяли местами указатели, parent все еще указывает на текущий cur_node
                _replaceChild(parent, cur_node, nullptr);
            }
            delete child;

        } else {
            Node* temp {cur_node};
            if (cur_node->left)
                cur_node = cur_node->left;
            else
                cur_node = cur_node->right;
            delete temp;
        }
        --_size;
    }

    return cur_node;
}

template <class DataType, class Comparator>
BinaryTreeRecursive<DataType, Comparator>::const_iterator
BinaryTreeRecursive<DataType, Comparator>::erase(const_iterator it) {
    Node* node2delete {it.ptr_stack.top()};
    BasicIterator new_it {it};
    ++new_it;
    _root = _erase(_root, node2delete);

    return new_it;
}

template <class DataType, class Comparator>
void BinaryTreeRecursive<DataType, Comparator>::_replaceChild(Node* parent, Node* old_child, Node* new_child) noexcept {
    if (parent->left == old_child)
        parent->left = new_child;
    else
        parent->right = new_child;
}

template <class DataType, class Comparator>
void BinaryTreeRecursive<DataType, Comparator>::_toVector(Node* cur_node, std::size_t& cur_index,
                                                          std::vector<DataType>& res) const {
    if (!cur_node)
        return;
    _toVector(cur_node->left, cur_index, res);
    res[cur_index++] = cur_node->val;
    _toVector(cur_node->right, cur_index, res);
}
