from __future__ import annotations


class BinaryTreeRecursive:
    """Реализация бинарного дерева с помощью рекурсии"""
    class _Node:
        def __init__(self, obj):
            self.obj = obj
            self.left: BinaryTreeRecursive._Node | None = None
            self.right: BinaryTreeRecursive._Node | None = None

        def __str__(self):
            return str(self.obj)

        def __repr__(self):
            return f"Node {{obj: {str(self.obj)}}}"

    def __init__(self, *args):
        self._root: BinaryTreeRecursive._Node | None = None
        self._size: int = 0
        for arg in args:
            self.insert(arg)

    def __str__(self):
        return f"BinaryTree [{', '.join(map(str, self))}]"

    def __len__(self):
        return self._size

    def __iter__(self):
        return self._treeIterator(self._root)

    def __contains__(self, obj):
        cur_node: BinaryTreeRecursive._Node | None = self._root
        while cur_node:
            if obj < cur_node.obj:
                cur_node = cur_node.left
            elif obj > cur_node.obj:
                cur_node = cur_node.right
            else:
                return True
        return False

    def _findMin(self, cur_node: BinaryTreeRecursive._Node):
        while cur_node.left:
            cur_node = cur_node.left
        return cur_node.obj

    def _insert(self, cur_node: BinaryTreeRecursive._Node | None, obj) -> BinaryTreeRecursive._Node:
        if not cur_node:
            self._size += 1
            return BinaryTreeRecursive._Node(obj)

        if obj < cur_node.obj:
            cur_node.left = self._insert(cur_node.left, obj)

        elif obj > cur_node.obj:
            cur_node.right = self._insert(cur_node.right, obj)

        return cur_node

    def insert(self, obj) -> None:
        self._root = self._insert(self._root, obj)

    def _remove(self, cur_node: BinaryTreeRecursive._Node | None, obj) -> BinaryTreeRecursive._Node | None:
        if not cur_node:
            raise KeyError(obj)

        if obj < cur_node.obj:
            cur_node.left = self._remove(cur_node.left, obj)
            return cur_node
        if obj > cur_node.obj:
            cur_node.right = self._remove(cur_node.right, obj)
            return cur_node

        # obj == cur_node.obj
        if not cur_node.left:
            self._size -= 1
            return cur_node.right
        if not cur_node.right:
            self._size -= 1
            return cur_node.left

        new_obj = self._findMin(cur_node.right)
        cur_node.obj = new_obj
        cur_node.right = self._remove(cur_node.right, new_obj)
        return cur_node

    def remove(self, obj) -> None:
        self._root = self._remove(self._root, obj)

    def _discard(self, cur_node: BinaryTreeRecursive._Node | None, obj) -> BinaryTreeRecursive._Node | None:
        if not cur_node:
            return None

        if obj < cur_node.obj:
            cur_node.left = self._discard(cur_node.left, obj)
            return cur_node
        if obj > cur_node.obj:
            cur_node.right = self._discard(cur_node.right, obj)
            return cur_node

        # obj == cur_node.obj
        if not cur_node.left:
            self._size -= 1
            return cur_node.right
        if not cur_node.right:
            self._size -= 1
            return cur_node.left

        new_obj = self._findMin(cur_node.right)
        cur_node.obj = new_obj
        cur_node.right = self._discard(cur_node.right, new_obj)
        return cur_node

    def discard(self, obj) -> None:
        self._root = self._discard(self._root, obj)

    def _toList(self, cur_node: BinaryTreeRecursive._Node | None, res: list) -> None:
        if not cur_node:
            return

        self._toList(cur_node.left, res)
        res.append(cur_node.obj)
        self._toList(cur_node.right, res)

    def toList(self) -> list:
        res: list = []
        self._toList(self._root, res)
        return res

    def _treeIterator(self, cur_node: BinaryTreeRecursive._Node | None):
        if not cur_node:
            return
        yield from self._treeIterator(cur_node.left)
        yield cur_node.obj
        yield from self._treeIterator(cur_node.right)


if __name__ == "__main__":
    print(BinaryTreeRecursive.__doc__)
    import timeit
    time_arr = timeit.repeat(setup="from BinaryTreeRecursive import BinaryTreeRecursive",
                             stmt="BinaryTreeRecursive(*list(range(500)))",
                             repeat=10, number=100)
    time_arr.sort()
    for time in time_arr:
        print(time)
