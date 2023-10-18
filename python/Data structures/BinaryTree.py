class BinaryTree:
    class __Binary_Node:
        def __init__(self, val=None):
            self.val = val
            self.left = None
            self.right = None
    def __init__(self, *args):
        if not args:
            self.__root = self.__Binary_Node()
            self.__size = 0
        else:
            self.__root = self.__Binary_Node(args[0])
            for i in range(1, len(args)):
                self.insert(args[i])

    def __str__(self):
        return str(self.to_list())

    def insert(self, val, root=None, first_step=True) -> None:
        if first_step:
            root = self.__root
            if not self.__root.val:
                self.__root.val = val
                return
            first_step = False

        if val < root.val:
            if root.left is None:
                root.left = self.__Binary_Node(val)
                return
            self.insert(val, root.left, first_step)

        elif val > root.val:
            if root.right is None:
                root.right = self.__Binary_Node(val)
                return
            self.insert(val, root.right, first_step)

    def to_list(self, root=None, res=None) -> list:
        if root is None:
            res = []
            root = self.__root
        if root.left:
            self.to_list(root.left, res)
        res.append(root.val)
        if root.right:
            self.to_list(root.right, res)
        return res
