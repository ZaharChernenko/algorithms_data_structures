#include <iostream>
#include "BinaryTree.h"
using std::cin, std::cout;


int main() {
    BinaryTree<int> tree {42, 2, 3, 59};
    cout << tree << ' ' << tree.size() << '\n';
    return 0;
}
