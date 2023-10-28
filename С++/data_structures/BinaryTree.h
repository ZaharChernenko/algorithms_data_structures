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

public:
    BinaryTree();
    BinaryTree(std::initializer_list<T> args);

    template<class T1> friend std::ostream& operator<<(std::ostream& os, const BinaryTree<T1>& tree);

    void insert(const T& val, BinaryNode* cur_node=nullptr);
    [[nodiscard]] std::vector<T> toVector(BinaryNode* cur_node=nullptr, std::vector<T>& res=std::vector<T>{}) const;
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
    /* метод toVector должен обязательно быть const, иначе код не будет компилироваться,
    так как мы передаем объект по константной ссылке, поэтому он не должен быть изменен,
    гарантию его сохранности дает const*/
    os << '[';
    for (std::size_t i = 0; i != vec_from_tree.size(); ++i) {
        os << vec_from_tree[i];
        if (i != vec_from_tree.size() - 1) os << ", ";
    }
    return os << ']';
}


template <class T>
void BinaryTree<T>::insert(const T &val, BinaryNode* cur_node) {
    if (cur_node == nullptr) {
        if (_root == nullptr) {
            _root = new BinaryNode(val);
            ++_size;
            return;
        }
        cur_node = _root;
    }

    if (cur_node->val > val) {
        if (cur_node->left == nullptr) {
            cur_node->left = new BinaryNode(val);
            ++_size;
            return;
        }
        else insert(val, cur_node->left);
    }

    else {
        if (cur_node->right == nullptr) {
            cur_node->right = new BinaryNode(val);
            ++_size;
            return;
        }
        else insert(val, cur_node->right);
    }
}


template <class T>
std::vector<T> BinaryTree<T>::toVector(BinaryNode* cur_node, std::vector<T>& res) const {
    if (cur_node == nullptr) {
        if (_root == nullptr) return res;
        cur_node = _root;
    }

    if (cur_node->left != nullptr) toVector(cur_node->left, res);
    res.push_back(cur_node->val);
    if (cur_node->right != nullptr) toVector(cur_node->right, res);

    return res;
}