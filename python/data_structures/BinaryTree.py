class BinaryTree:
    class __Binary_Node:
        def __init__(self, val=None):
            self.val = val
            self.left = None
            self.right = None

    def __init__(self, *args):
        if not args:
            self.__root = None
            self.__size = 0
        else:
            self.__root = self.__Binary_Node(args[0])
            self.__size = 1
            for i in range(1, len(args)):
                self.__insert(args[i])

    def __str__(self):
        return str(self.to_list())

    def __len__(self):
        return self.__size

    def __insert(self, val) -> None:
        parent = None
        cur_node = self.__root

        while cur_node is not None:
            parent = cur_node

            if cur_node.val > val:
                cur_node = cur_node.left
            elif cur_node.val < val:
                cur_node = cur_node.right
            else:
                return

        if parent is None:
            self.__root = self.__Binary_Node(val)
        elif parent.val > val:
            parent.left = self.__Binary_Node(val)
        else:
            parent.right = self.__Binary_Node(val)

        self.__size += 1

    """ Рекурсивная реализация вставки, по идее менее эффективная, чем цикл
        def insert(self, val, root=None) -> None:
        if root is None:
            if self.__root is None:
                self.__root = self.__Binary_Node(val)
                self.__size += 1
                return
            root = self.__root

        if val < root.val:
            if root.left is None:
                root.left = self.__Binary_Node(val)
                self.__size += 1
                return
            self.insert(val, root.left)

        elif val > root.val:
            if root.right is None:
                root.right = self.__Binary_Node(val)
                self.__size += 1
                return
            self.insert(val, root.right)
    """
    def __remove(self, cur_node: __Binary_Node, val):
        parent = None
        while cur_node is not None and cur_node.val != val:
            parent = cur_node
            if cur_node.val > val:
                cur_node = cur_node.left
            elif cur_node.val < val:
                cur_node = cur_node.right

        if cur_node is None:
            raise KeyError

        new_node = None

        if cur_node.left is None:
            new_node = cur_node.right
        elif cur_node.right is None:
            new_node = cur_node.left
        else:
            min_node_parent = cur_node
            min_node = cur_node.right
            while min_node.left is not None:
                min_node_parent = min_node
                min_node = min_node.left
            self.__replaceChild(min_node_parent, min_node, min_node.right)

            new_node = cur_node
            cur_node.val = min_node.val

        self.__replaceChild(parent, old=cur_node, new=new_node)
        self.__size -= 1

    def __replaceChild(self, parent: __Binary_Node,
                       old: __Binary_Node, new: __Binary_Node):
        if parent is None:
            self.__root = new
        elif parent.left == old:
            parent.left = new
        elif parent.right == old:
            parent.right = new

    def __discard(self, cur_node: __Binary_Node, val):
        if cur_node is None:
            return cur_node
        if cur_node.val > val:
            cur_node.left = self.__discard(cur_node.left, val)
            return cur_node
        if cur_node.val < val:
            cur_node.right = self.__discard(cur_node.right, val)
            return cur_node

        assert cur_node.val == val, "something unexpected"
        if cur_node.left is not None and cur_node.right is not None:
            min_val = self.__findMin(cur_node.right)
            cur_node.val = min_val
            cur_node.right = self.__discard(cur_node.right, min_val)
            return cur_node

        new_node = None
        if cur_node.left is None:
            new_node = cur_node.right
        if cur_node.right is None:
            new_node = cur_node.left
        self.__size -= 1
        return new_node

    def __findMin(self, cur_node: __Binary_Node):
        while cur_node.left is not None:
            cur_node = cur_node.left
        return cur_node.val

    def __to_list(self, cur_node, res: list) -> list:
        if cur_node is None:
            return res

        if cur_node.left: self.__to_list(cur_node.left, res)
        res.append(cur_node.val)
        if cur_node.right: self.__to_list(cur_node.right, res)

        return res

    def insert(self, val):  # инкапсуляция необходима, чтобы пользователь не добавил какой-то неизвестный корень
        self.__insert(val)

    def remove(self, val):
        self.__remove(self.__root, val)

    def discard(self, val):
        self.__root = self.__discard(self.__root, val)

    def to_list(self):
        return self.__to_list(self.__root, [])
