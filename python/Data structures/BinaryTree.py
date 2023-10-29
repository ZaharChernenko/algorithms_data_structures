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
        return str(self.__to_list())

    def __insert(self, val) -> None:
        parent = None
        cur_node = self.__root

        while cur_node is not None:
            parent = cur_node

            if cur_node.val > val :
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

    def __to_list(self, cur_node=None, res=None) -> list:
        if cur_node is None:
            res = []
            if self.__root is None: return res
            cur_node = self.__root

        if cur_node.left: self.__to_list(cur_node.left, res)
        res.append(cur_node.val)
        if cur_node.right: self.__to_list(cur_node.right, res)

        return res

    def __remove(self, key, cur_node=None, is_zero_step=True) -> None:
        if cur_node is None:
            if not is_zero_step:
                raise KeyError
            cur_node = self.__root
            is_zero_step = False

        if cur_node.val == key:
            if cur_node.left is not None and cur_node.right is not None:
                temp = cur_node.right
                if temp.left is None:
                    cur_node.val = temp.val
                    cur_node.right
                while temp.left is not None:
                    temp = temp.left


        elif cur_node.val > key:
            self.__remove(key, cur_node.left, is_zero_step)

        else:
            self.__remove(key, cur_node.right, is_zero_step)

    def insert(self, val): # инкапсуляция необходима, чтобы пользователь не добавил какой-то неизвестный корень
        self.__insert(val)

    def to_list(self):
        return self.__to_list()
