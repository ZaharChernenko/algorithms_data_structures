from __future__ import annotations


class SingleLinkedList:
    """Односвязный список:
    Добавить в конец или начало: O(1)
    Вставить: O(n)
    Удалить начало: O(1)
    Удалить любой другой элемент: O(n)
    Проверка членства: O(n)"""
    class _Node:
        def __init__(self, obj, p_next: SingleLinkedList._Node | None = None):
            self.obj = obj
            self.p_next = p_next

        def __str__(self):
            return str(self.obj)

        def __repr__(self):
            return f"Node {{obj: {self.obj}}}"

    class _Iterator:
        def __init__(self, node: SingleLinkedList._Node | None):
            self.node = node

        def __iter__(self):
            return self

        def __next__(self):
            if self.node:
                temp = self.node
                self.node = self.node.p_next
                return temp
            raise StopIteration

    def __init__(self, *args):
        self._front: SingleLinkedList._Node | None = None
        self._back: SingleLinkedList._Node | None = None
        self._size: int = 0
        for arg in args:
            self.pushBack(arg)

    def __str__(self):
        return f"SingleLinkedList [{', '.join(map(str, self))}]"

    def __len__(self):
        return self._size

    def __getitem__(self, index: int):
        if index < 0:
            index += self._size

        if index >= self._size or index < 0:
            raise IndexError("list index out of range")

        cur_node = self._front
        for _ in range(index):
            cur_node = cur_node.p_next
        return cur_node.obj

    def __setitem__(self, index: int, obj):
        if index < 0:
            index += self._size

        if index >= self._size or index < 0:
            raise IndexError("list assignment index out of range")

        cur_node = self._front
        for _ in range(index):
            cur_node = cur_node.p_next
        cur_node.obj = obj

    def __delitem__(self, index: int):
        if index < 0:
            index += self._size

        if index >= self._size or index < 0:
            raise IndexError("list assignment index out of range")

        if index == 0:
            self._front = self._front.p_next
            if not self._front:
                self._back = self._front
        else:
            cur_node = self._front
            for _ in range(index - 1):  # если быть точным, здесь выполняется n - 2 операции
                cur_node = cur_node.p_next  # т.к. index начинается с 0, т.е. на 1 меньше
                # это связано с тем, что нам не нужно работать с первым и последним элементами
            if cur_node.p_next == self._back:
                self._back = cur_node
            cur_node.p_next = cur_node.p_next.p_next
        self._size -= 1

    def __iter__(self):
        return SingleLinkedList._Iterator(self._front)

    def __contains__(self, obj):
        cur_node = self._front
        for _ in range(self._size):
            if obj == cur_node.obj:
                return True
            cur_node = cur_node.p_next
        return False

    def pushFront(self, obj):
        if not self._front:
            self._front = self._back = SingleLinkedList._Node(obj)
        else:
            self._front = SingleLinkedList._Node(obj, self._front)

        self._size += 1

    def pushBack(self, obj):
        new_node: SingleLinkedList._Node = SingleLinkedList._Node(obj)

        if not self._back:
            self._front = self._back = new_node
        else:
            self._back.p_next = new_node
            self._back = self._back.p_next

        self._size += 1

    def insert(self, index: int, obj):
        if index < 0:
            index += self._size

        if index <= 0:
            self.pushFront(obj)
        elif index >= self._size:
            self.pushBack(obj)
        else:
            cur_node = self._front
            for _ in range(index - 1):
                cur_node = cur_node.p_next
            cur_node.p_next = SingleLinkedList._Node(obj, cur_node.p_next)
            self._size += 1

    def extend(self, iterable):
        for elem in iterable:
            self.pushBack(elem)

    def popFront(self):
        if not self._front:
            raise IndexError("pop from empty list")

        obj = self._front.obj
        self._front = self._front.p_next
        if not self._front:
            self._back = self._front

        self._size -= 1
        return obj

    def pop(self, index: int = 0):
        if self._size == 0:
            raise IndexError("pop from empty list")

        if index == 0:
            return self.popFront()

        if index < 0:
            index += self._size

        if index < 0 or index >= self._size:
            raise IndexError("pop index out of range")

        cur_node = self._front
        for _ in range(index - 1):
            cur_node = cur_node.p_next
        obj = cur_node.p_next.obj
        cur_node.p_next = cur_node.p_next.p_next

        self._size -= 1
        return obj

    def remove(self, obj):
        if not self._front:
            raise IndexError("remove from empty list")

        if self._front.obj == obj:
            self._front = self._front.p_next
            if not self._front:
                self._back = self._front
            self._size -= 1
            return

        cur_node: SingleLinkedList._Node | None = self._front
        for _ in range(self._size - 1):  # первый элемент мы проверили, осталось проверить n - 1
            if cur_node.p_next.obj == obj:
                cur_node.p_next = cur_node.p_next.p_next
                self._size -= 1
                return
            cur_node = cur_node.p_next

        raise ValueError(f"remove: {obj} not in list")

    def front(self):
        if not self._front:
            raise IndexError("list is empty")
        return self._front.obj

    def back(self):
        if not self._back:
            raise IndexError("list is empty")
        return self._back.obj

    def toList(self) -> list:
        return list(self)


l = SingleLinkedList(1, 2, 3, 4)
print(l.remove(5))
print(l, len(l))
