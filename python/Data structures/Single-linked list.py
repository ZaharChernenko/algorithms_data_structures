class SingleLinkedList:
    class _ListNode:
        def __init__(self, val=None, next=None):
            self.val = val
            self.next = next

        def __str__(self):
            return f"ListNode{{val: {self.val}, next: {self.next}}}"

    def __init__(self):
        self._head = None
        self._tail = None
        self._size = 0

    def __getitem__(self, item):
        if item >= self._size or item < -self._size:
            raise IndexError
        else:
            temp = self._head
            if item < 0:
                item = self._size + item
            for i in range(item):
                temp = temp.next
            return temp

    def __setitem__(self, key, value):
        if key >= self._size or key < -self._size:
            raise IndexError
        else:
            temp = self._head
            if key < 0:
                key = self._size + key
            for i in range(key):
                temp = temp.next
            temp.val = value

    def __str__(self):
        return self._head.__str__()

    def pushFront(self, val):
        if self._size == 0:
            self._head = self._ListNode(val)
            self._tail = self._head
            self._size = 1
        else:
            self._head = self._ListNode(val, self._head)
            self._size += 1
    def pushBack(self, val):
        if self._size == 0:
            self._head = self._ListNode(val)
            self._tail = self._head
            self._size = 1
        else:
            self._tail.next = self._ListNode(val)
            self._tail = self._tail.next
            self._size += 1

    def popFront(self):
        if self._size != 0:
            temp = self._head.val
            self._head = self._head.next
            self._size -= 1
            return temp
        else:
            raise IndexError

    def popBack(self):
        if self._size == 1:
            temp_val = self._head.val
            self._head = None
            self._size -= 1
            return temp_val

        elif self._size > 1:
            temp = self._head
            for i in range(self._size - 2):
                temp = temp.next
            temp_val = temp.next.val
            self._tail = temp
            self._tail.next = None
            self._size -= 1
            return temp_val

        else:
            raise IndexError

lst = SingleLinkedList()


lst.pushBack(2)
lst.pushBack(3)
print(lst)
