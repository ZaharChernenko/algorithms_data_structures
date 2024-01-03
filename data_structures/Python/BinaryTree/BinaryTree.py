from __future__ import annotations


class BinaryTree:
    """Реализация бинарного дерева с помощью цикла"""
    class _Node:
        def __init__(self, obj):
            self.obj = obj
            self.left: BinaryTree._Node | None = None
            self.right: BinaryTree._Node | None = None

        def __str__(self):
            return str(self.obj)

        def __repr__(self):
            return f"Node {{obj: {str(self.obj)}}}"

    class _TreeIterator:
        def __init__(self, cur_node: BinaryTree._Node | None):
            self.stack: list = []

            while cur_node:
                self.stack.append(cur_node)
                cur_node = cur_node.left

        def __iter__(self):
            return self

        def __next__(self):
            if not self.stack:
                raise StopIteration
            cur_node = self.stack.pop()

            new_node = cur_node.right
            while new_node:
                self.stack.append(new_node)
                new_node = new_node.left

            return cur_node.obj

    def __init__(self, *args):
        self._root: BinaryTree._Node | None = None
        self._size: int = 0
        for arg in args:
            self.insert(arg)

    def __str__(self):
        return f"BinaryTree [{', '.join(map(str, self))}]"

    def __len__(self):
        return self._size

    def __iter__(self):
        return self._TreeIterator(self._root)

    def __contains__(self, obj):
        cur_node: BinaryTree._Node | None = self._root
        while cur_node:
            if obj < cur_node.obj:
                cur_node = cur_node.left
            elif obj > cur_node.obj:
                cur_node = cur_node.right
            else:
                return True
        return False

    def _replaceChild(self, parent, old_child, new_child):
        if not parent:
            self._root = new_child
        elif parent.left is old_child:
            parent.left = new_child
        else:
            parent.right = new_child

    def insert(self, obj):
        parent: BinaryTree._Node | None = None
        cur_node = self._root

        while cur_node:
            if obj < cur_node.obj:
                parent = cur_node
                cur_node = cur_node.left
            elif obj > cur_node.obj:
                parent = cur_node
                cur_node = cur_node.right
            else:
                return

        new_node = BinaryTree._Node(obj)
        if not parent:
            self._root = new_node
        elif obj < parent.obj:
            parent.left = new_node
        else:
            parent.right = new_node
        self._size += 1

    def remove(self, obj):
        parent: BinaryTree._Node | None = None
        cur_node = self._root

        while cur_node:
            if obj < cur_node.obj:
                parent = cur_node
                cur_node = cur_node.left
            elif obj > cur_node.obj:
                parent = cur_node
                cur_node = cur_node.right
            else:
                break

        if not cur_node:
            raise KeyError(obj)

        if not cur_node.left:
            new_node = cur_node.right
        elif not cur_node.right:
            new_node = cur_node.left
        else:
            min_node_parent = cur_node
            min_node = cur_node.right
            while min_node.left:
                min_node_parent = min_node
                min_node = min_node.left
            cur_node.obj = min_node.obj
            new_node = cur_node
            self._replaceChild(min_node_parent, min_node, min_node.right)
        self._replaceChild(parent, cur_node, new_node)
        self._size -= 1

    def discard(self, obj):
        parent: BinaryTree._Node | None = None
        cur_node = self._root

        while cur_node:
            if obj < cur_node.obj:
                parent = cur_node
                cur_node = cur_node.left
            elif obj > cur_node.obj:
                parent = cur_node
                cur_node = cur_node.right
            else:
                break

        if not cur_node:
            return

        if not cur_node.left:
            new_node = cur_node.right
        elif not cur_node.right:
            new_node = cur_node.left
        else:
            min_node_parent = cur_node
            min_node = cur_node.right
            while min_node.left:
                min_node_parent = min_node
                min_node = min_node.left
            cur_node.obj = min_node.obj
            new_node = cur_node
            self._replaceChild(min_node_parent, min_node, min_node.right)
        self._replaceChild(parent, cur_node, new_node)
        self._size -= 1

    def _toList(self, cur_node: BinaryTree._Node | None, res: list) -> None:
        if not cur_node:
            return

        self._toList(cur_node.left, res)
        res.append(cur_node.obj)
        self._toList(cur_node.right, res)

    def toList(self) -> list:
        res: list = []
        self._toList(self._root, res)
        return res


if __name__ == "__main__":
    print(BinaryTree.__doc__)
    import timeit
    time_arr = timeit.repeat(setup="from BinaryTree import BinaryTree",
                             stmt="BinaryTree(*list(range(500)))",
                             repeat=10, number=100)
    time_arr.sort()
    for time in time_arr:
        print(time)


# https://acm.bsu.by/wiki/Программная_реализация_бинарных_поисковых_деревьев#.D0.A3.D0.B4.D0.B0.D0.BB.D0.B5.D0.BD.D0.B8.D0.B5_.D0.B8.D0.B7_.D0.B4.D0.B5.D1.80.D0.B5.D0.B2.D0.B0
