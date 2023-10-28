#include <iostream>
#include "Queue.h"
#include "BinaryTree.h"
#include <vector>

using std::cin, std::cout;


int main() {
    BinaryTree<int> tree {42, 2, 3, 59, 23};
    tree.insert(99);
    cout << tree;
    return 0;
}
