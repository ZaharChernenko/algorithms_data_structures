from __future__ import annotations


class MyQueue:
    """Очередь на основе односвязного списка, операции по добавлению элементов
в начало и конец имеет сложность O(1), остальные - O(n)"""
    class _Node:
        def __init__(self, obj, p_next: MyQueue._Node | None = None):
            self.obj = obj
            self.p_next = p_next

        def __str__(self):
            return str(self.obj)  # return f"Node {{obj = {self.obj}, next = {self.p_next}}}"

    def __init__(self, *args):
        self._front: MyQueue._Node | None = None
        self._back: MyQueue._Node | None = None
        self._size: int = 0
        for arg in args:
            self.pushBack(arg)

    def __str__(self):
        return f"Queue [{', '.join(map(str, self))}]"

    def __len__(self):
        return self._size

    def __getitem__(self, index: int):
        if index < 0:
            index += self._size

        if index >= self._size or index < 0:
            raise IndexError("queue assignment index out of range")

        cur_node = self._front
        for _ in range(index):
            cur_node = cur_node.p_next
        return cur_node.obj

    def __setitem__(self, index: int, obj):
        if index < 0:
            index += self._size

        if index >= self._size or index < 0:
            raise IndexError("queue assignment index out of range")

        cur_node = self._front
        for _ in range(index):
            cur_node = cur_node.p_next
        cur_node.obj = obj

    def __delitem__(self, index: int):
        if index < 0:
            index += self._size

        if index >= self._size or index < 0:
            raise IndexError("queue assignment index out of range")

        if index == 0:
            self._front = self._front.p_next
            if not self._front:
                self._back = self._front
        else:
            cur_node = self._front
            for _ in range(index - 1):
                cur_node = cur_node.p_next

            if cur_node.p_next == self._back:
                self._back = cur_node
            cur_node.p_next = cur_node.p_next.p_next
        self._size -= 1

    def __iter__(self):
        return self.QueueIterator(self._front)

    class QueueIterator:
        def __init__(self, front: MyQueue._Node | None):
            self.cur_node = MyQueue._Node(None, front)

        def __iter__(self):
            return self

        def __next__(self):
            if self.cur_node.p_next is not None:
                self.cur_node = self.cur_node.p_next
                return self.cur_node
            raise StopIteration

    def toList(self) -> list:
        res = [0] * self._size
        cur_node = self._front
        for i in range(self._size):
            res[i] = cur_node.obj
            cur_node = cur_node.p_next
        return res

    def pushFront(self, obj):  # сложность операции O(1)
        if not self._front:
            self._front = self._back = self._Node(obj)
        else:
            self._front = self._Node(obj, self._front)
        self._size += 1

    def pushBack(self, obj):  # сложность операции O(1)
        if not self._back:
            self._front = self._back = self._Node(obj)
        else:
            self._back.p_next = self._Node(obj)
            self._back = self._back.p_next
        self._size += 1

    def insert(self, index: int, obj):
        if index < 0:
            index += self._size
        if index == 0:
            self.pushFront(obj)
        elif index >= self._size:
            self.pushBack(obj)
        else:
            cur_node = self._front
            for _ in range(index - 1):
                cur_node = cur_node.p_next
            cur_node.p_next = self._Node(obj, cur_node.p_next)
            self._size += 1

    def popFront(self):  # O(1)
        if not self._front:
            raise IndexError("pop from empty queue")
        obj = self._front.obj
        self._front = self._front.p_next
        if self._front is None:
            self._back = self._front
        self._size -= 1
        return obj

    def popBack(self):  # O(n)
        if not self._back:
            raise IndexError("pop from empty queue")
        obj = self._back.obj
        self._size -= 1
        if self._size == 0:
            self._front = self._back = None
        else:
            temp = self._back
            self._back = self._front
            while self._back.p_next != temp:
                self._back = self._back.p_next
            self._back.p_next = None
        return obj

    def front(self):
        if self._size == 0:
            raise IndexError("queue is empty")
        return self._front.obj

    def back(self):
        if self._size == 0:
            raise IndexError("queue is empty")
        return self._back.obj
