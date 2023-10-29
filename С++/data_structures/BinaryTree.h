#pragma once
#include <iostream>
#include <vector>

template <class T>
class BinaryTree {
private:
    struct BinaryNode {
        T val;
        BinaryNode* left;
        BinaryNode* right;
        BinaryNode(T val={});
    };

    BinaryNode* _root;
    std::size_t _size;

    BinaryNode* _insert(const T& val, BinaryNode* cur_node);
    std::vector<T> _toVector(BinaryNode* cur_node, std::vector<T>& res) const;

public:
    BinaryTree();
    BinaryTree(std::initializer_list<T> args);

    template<class T1> friend std::ostream& operator<<(std::ostream& os, const BinaryTree<T1>& tree);

    void insert(const T& val);
    [[nodiscard]] std::vector<T> toVector() const;
};


template <class T>
BinaryTree<T>::BinaryNode::BinaryNode(T val): val{val}, left{nullptr}, right{nullptr} {}


template <class T>
BinaryTree<T>::BinaryTree():
    _root{nullptr}, _size{0} {
    std::cout << "Default constructor was used\n";
}


template <class T>
BinaryTree<T>::BinaryTree(std::initializer_list<T> args):
    _root{new BinaryNode(*args.begin())}, _size{1} {
    for (auto i = args.begin() + 1; i != args.end(); ++i) {
        insert(*i);
    }
    std::cout << "Constructor with args was used\n";
}


template <class T1>
std::ostream& operator<<(std::ostream& os, const BinaryTree<T1>& tree) {
    std::vector<T1> vec_from_tree {tree.toVector()};
    /* ����� toVector ������ ����������� ���� const, ����� ��� �� ����� ���������������,
    ��� ��� �� �������� ������ �� ����������� ������, ������� �� �� ������ ���� �������,
    �������� ��� ����������� ���� const*/
    os << '[';
    for (std::size_t i = 0; i != vec_from_tree.size(); ++i) {
        os << vec_from_tree[i];
        if (i != vec_from_tree.size() - 1) os << ", ";
    }
    return os << ']';
}


template <class T>
typename BinaryTree<T>::BinaryNode* BinaryTree<T>::_insert(const T &val, BinaryNode* cur_node) {
    if (cur_node == nullptr) return new BinaryNode(val);
    if (cur_node->val > val) cur_node->left = _insert(val, cur_node->left);
    else if (cur_node->val < val) cur_node->right = _insert(val, cur_node->right);
    return cur_node;
}


template <class T>
std::vector<T> BinaryTree<T>::_toVector(BinaryNode* cur_node, std::vector<T>& res) const {
    if (cur_node == nullptr) return res;

    if (cur_node->left != nullptr) _toVector(cur_node->left, res);
    res.push_back(cur_node->val);
    if (cur_node->right != nullptr) _toVector(cur_node->right, res);

    return res;
}


template <class T>
void BinaryTree<T>::insert(const T &val) {
    _root = _insert(val, _root);
}


template <class T>
std::vector<T> BinaryTree<T>::toVector() const {
    std::vector<T> res{};
    _toVector(_root, res);
    return res;
}