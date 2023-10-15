class Queue:
    class __Node:
        def __init__(self, val=None, next=None):
            self.val = val
            self.next = next

        """def __str__(self):
            return str(self.val)"""

        def __str__(self):
            return f"Node {{val = {self.val}, next = {self.next}}}"

    def __init__(self, *args):
        if not args:
            self.__head = self.__tail = None
            self.__size = 0
        else:
            self.__head = self.__tail = self.__Node(args[0])
            self.__size = 1
            for i in range(1, len(args)):
                self.pushBack(args[i])

    """def __str__(self):
        s = "["
        temp = self.__head
        for i in range(self.__size):
            s += temp.__str__()
            if i != self.__size - 1:
                s += ", "
            temp = temp.next
        return s + "]" """

    def __str__(self):
        return self.__head.__str__()

    def __len__(self):
        return self.__size

    def __getitem__(self, item):
        if item < -self.__size or item >= self.__size:
            raise IndexError
        if item < 0:
            item += self.__size
        temp = self.__head
        for i in range(item):
            temp = temp.next
        return temp

    def __setitem__(self, key, value):
        if key < -self.__size or key >= self.__size:
            raise IndexError
        if key < 0:
            key += self.__size
        temp = self.__head
        for i in range(key):
            temp = temp.next
        temp.val = value

    def pushFront(self, val):  # сложность операции O(1)
        if not self.__head:
            self.__head = self.__tail = self.__Node(val)
        else:
            self.__head = self.__Node(val, self.__head)
        self.__size += 1

    def pushBack(self, val):  # сложность операции O(1)
        if not self.__head:
            self.__head = self.__tail = self.__Node(val)
        else:
            self.__tail.next = self.__Node(val)
            self.__tail = self.__tail.next
        self.__size += 1

    def popFront(self):  # O(1)
        if self.__size == 0:
            raise IndexError
        val = self.__head.val
        self.__head = self.__head.next
        self.__size -= 1
        return val

    def popBack(self):  # O(n)
        if self.__size == 0:
            raise IndexError
        if self.__size == 1:
            val = self.__head.val
            self.__head = self.__tail = None
            self.__size = 0
            return val
        val = self.__tail.val
        self.__tail = self[-2]
        self.__tail.next = None
        self.__size -= 1
        return val

q = Queue(*range(10))
print(q[10].val)