#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <exception>


enum BinaryTreeErrors {
    KEY_ERROR = 4
};


class BinaryTreeException : public std::exception {
private:
    std::unordered_map<BinaryTreeErrors, const char*> errors_map{ {KEY_ERROR, "\nKey error\n"}};
    const char* _msg;
public:
    BinaryTreeException(BinaryTreeErrors e) : _msg{ errors_map[e] } {};
    [[nodiscard]] const char* what() const noexcept override {
        return _msg;
    }
};


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

    BinaryNode* _insert(BinaryNode* cur_node, const T& val);
    BinaryNode* _remove(BinaryNode* cur_node, const T& val);
    BinaryNode* _discard(BinaryNode* cur_node, const T& val);
    T _findMin(BinaryNode* cur_node);

    void _deleteTree(BinaryNode* cur_node);
    void _toVector(BinaryNode* cur_node, std::vector<T>& res) const;
    /*VS позволяет сделать std::vector<T>& res=std::vector<T>{}, однако в CLION это не работает
    как и в большинстве компиляторов, так как std::vector<T>{} - временный объект, который может быть
    удален, соответственно ссылки на него быть не может*/

public:
    BinaryTree();
    BinaryTree(std::initializer_list<T> args);
    ~BinaryTree();

    template<class T1> friend std::ostream& operator<<(std::ostream& os, const BinaryTree<T1>& tree);

    [[nodiscard]] std::size_t size() const;
    void insert(const T& val);
    void remove(const T& val);
    void discard(const T& val); // doesn't throw an exception if val is not found
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


template <class T>
BinaryTree<T>::~BinaryTree() {
    _deleteTree(_root);
    std::cout << "Destructor was called\n";
}


template <class T1>
std::ostream& operator<<(std::ostream& os, const BinaryTree<T1>& tree) {
    std::vector<T1> vec_from_tree {tree.toVector()};
    /*our BinaryTree object used as const reference, this is why
    all methods that called in this function also must be const*/
    os << '[';
    for (std::size_t i = 0; i != vec_from_tree.size(); ++i) {
        os << vec_from_tree[i];
        if (i != vec_from_tree.size() - 1) os << ", ";
    }
    return os << ']';
}


template <class T>
typename BinaryTree<T>::BinaryNode* BinaryTree<T>::_insert(BinaryNode* cur_node, const T& val) {
    if (cur_node == nullptr) {
        ++_size;
        return new BinaryNode(val);
    }
    if (cur_node->val > val) cur_node->left = _insert(cur_node->left, val);
    else if (cur_node->val < val) cur_node->right = _insert(cur_node->right, val);
    return cur_node;
}


template <class T>
typename BinaryTree<T>::BinaryNode* BinaryTree<T>::_remove(BinaryNode* cur_node, const T& val) {
    if (cur_node == nullptr) throw BinaryTreeException(BinaryTreeErrors::KEY_ERROR);

    if (cur_node->val > val) {
        cur_node->left = _remove(cur_node->left, val);
        return cur_node;
    }
    if (cur_node->val < val) {
        cur_node->right = _remove(cur_node->right, val);
        return cur_node;
    }

    // cur_node->val == val
    if (cur_node->left != nullptr && cur_node->right != nullptr) {
        T min_val = _findMin(cur_node->right);
        cur_node->val = min_val;
        cur_node->right = _remove(cur_node->right, min_val);
        return cur_node;
    }

    BinaryNode* new_node;
    if (cur_node->left == nullptr) new_node = cur_node->right;
    else if (cur_node->right == nullptr) new_node = cur_node->left;
    delete cur_node;
    --_size;
    return new_node;
}


template <class T>
typename BinaryTree<T>::BinaryNode* BinaryTree<T>::_discard(BinaryNode* cur_node, const T& val) {
    if (cur_node == nullptr) return cur_node;

    if (cur_node->val > val) {
        cur_node->left = _discard(cur_node->left, val);
        return cur_node;
    }
    if (cur_node->val < val) {
        cur_node->right = _discard(cur_node->right, val);
        return cur_node;
    }

    // cur_node->val == val
    if (cur_node->left != nullptr && cur_node->right != nullptr) {
        T min_val = _findMin(cur_node->right);
        cur_node->val = min_val;
        cur_node->right = _discard(cur_node->right, min_val);
        return cur_node;
    }

    BinaryNode* new_node;
    if (cur_node->left == nullptr) new_node = cur_node->right;
    else if (cur_node->right == nullptr) new_node = cur_node->left;
    delete cur_node;
    --_size;
    return new_node;
}


template <class T>
T BinaryTree<T>::_findMin(BinaryNode* cur_node) {
    while (cur_node->left != nullptr) {
        cur_node = cur_node->left;
    }
    return cur_node->val;
}


template <class T>
void BinaryTree<T>::_toVector(BinaryNode* cur_node, std::vector<T>& res) const {
    if (cur_node == nullptr) return;

    if (cur_node->left != nullptr) _toVector(cur_node->left, res);
    res.push_back(cur_node->val);
    if (cur_node->right != nullptr) _toVector(cur_node->right, res);
}


template <class T>
void BinaryTree<T>::_deleteTree(BinaryNode* cur_node) {
    if (cur_node != nullptr) {
        _deleteTree(cur_node->left);
        _deleteTree(cur_node->right);
        delete cur_node;
    }
}


template <class T>
std::size_t BinaryTree<T>::size() const {
    return _size;
}


template <class T>
void BinaryTree<T>::insert(const T &val) {
    _root = _insert(_root, val);
}


template <class T>
void BinaryTree<T>::remove(const T& val) {
    _root = _remove(_root, val);
}


template <class T>
void BinaryTree<T>::discard(const T& val) {
    _root = _discard(_root, val);
}


template <class T>
std::vector<T> BinaryTree<T>::toVector() const {
    std::vector<T> res{};
    _toVector(_root, res);
    return res;
}
