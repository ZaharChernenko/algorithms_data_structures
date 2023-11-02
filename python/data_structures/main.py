from MyQueue import MyQueue
from BinaryTree import BinaryTree

tree = BinaryTree(4, 3, 2, 1, 21)
tree.insert(-1)
print(tree, len(tree))
tree.remove(4)
tree.discard(21)
print(tree, len(tree))
