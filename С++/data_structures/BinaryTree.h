#pragma once
#include <iostream>

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

    void insert(const T& val, BinaryNode* root= nullptr);

    template<class T1> std::ostream friend operator<<(std::ostream os, const BinaryTree& q);

};


template <class T>
BinaryTree<T>::BinaryNode::BinaryNode(T val): val{val}, left{nullptr}, right{nullptr} {}


template <class T>
BinaryTree<T>::BinaryTree(): _root{nullptr}, _size{0} {
    std::cout << "Default constructor was used\n";
}


template <class T>
BinaryTree<T>::BinaryTree(std::initializer_list<T> args): _root{*args.begin(), _size{1}} {
    for (auto i = args.begin() + 1; i != args.end(); ++i)
    {

    }
    std::cout << "Constructor with args was used\n";
}


template <class T>
void BinaryTree<T>::insert(const T &val, BinaryNode* root) {
    if (_root == nullptr) {
        _root = new BinaryNode(val);
        ++_size;
        return;
    }
    if (root == nullptr) {

    }
    root
}