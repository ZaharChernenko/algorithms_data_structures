class MyQueue:
    """Очередь на основе односвязного списка, операции по добавлению элементов
    в начало и конец имеет сложность O(1),
    остальные - O(n)"""
    class __Node:
        def __init__(self, val=None, next=None):
            self.val = val
            self.next = next

        def __str__(self):
            return str(self.val)

        """def __str__(self):
            return f"Node {{val = {self.val}, next = {self.next}}}" """

    def __init__(self, *args):
        if not args:
            self.__front = self.__back = None
            self.__size = 0
        else:
            self.__front = self.__back = self.__Node(args[0])
            self.__size = 1
            for i in range(1, len(args)):
                self.pushBack(args[i])

    def __str__(self):
        s = "["
        temp = self.__front
        while temp is not None:
            s += temp.__str__()
            temp = temp.next
            if temp is None:
                break
            s += ", "
        return s + "]"

    """def __str__(self):
        return self.__head.__str__()"""

    def __len__(self):
        return self.__size

    def __getitem__(self, item):
        if item < 0:
            item += self.__size

        if item >= self.__size:
            raise IndexError

        temp = self.__front
        for i in range(item):
            temp = temp.next
        return temp.val

    def __setitem__(self, key, value):
        if key < 0:
            key += self.__size

        if key >= self.__size:
            raise IndexError

        temp = self.__front
        for i in range(key):
            temp = temp.next
        temp.val = value

    def __delitem__(self, key):
        if self.__size == 0:
            raise IndexError

        if key < 0:
            key += self.__size

        if key >= self.__size:
            raise IndexError

        if key == 0:
            self.__front = self.__front.next
            if self.__front is None:
                self.__back = self.__front
        else:
            temp = self.__front
            for i in range(1, key):
                temp = temp.next
            temp.next = temp.next.next
        self.__size -= 1

    def pushFront(self, val):  # сложность операции O(1)
        if not self.__front:
            self.__front = self.__back = self.__Node(val)
        else:
            self.__front = self.__Node(val, self.__front)
        self.__size += 1

    def pushBack(self, val):  # сложность операции O(1)
        if not self.__front:
            self.__front = self.__back = self.__Node(val)
        else:
            self.__back.next = self.__Node(val)
            self.__back = self.__back.next
        self.__size += 1

    def popFront(self):  # O(1)
        if self.__size == 0:
            raise IndexError
        val = self.__front.val
        self.__front = self.__front.next
        self.__size -= 1
        return val

    def popBack(self):  # O(n)
        if self.__size == 0:
            raise IndexError
        val = self.__back.val
        self.__size -= 1
        if self.__size == 0:
            self.__front = self.__back = None
        else:
            temp = self.__back
            self.__back = self.__front
            while self.__back.next != temp:
                self.__back = self.__back.next
            self.__back.next = None
        return val

    def insert(self, key, value):
        if key < 0:
            key += self.__size

        if key > self.__size:
            raise IndexError

        if key == 0:
            self.pushFront(value)
        elif key == self.__size:
            self.pushBack(value)
        else:
            temp = self.__front
            for i in range(1, key):
                temp = temp.next
            temp.next = self.__Node(value, temp.next)
            self.__size += 1

    def front(self):
        if self.__size == 0:
            raise IndexError
        return self.__front.val

    def back(self):
        if self.__size == 0:
            raise IndexError
        return self.__back.val
