from __future__ import annotations


def gt(first, second) -> bool:
    return first > second


def lt(first, second) -> bool:
    return first < second


class Heap:
    def __init__(self, *args, comp=lt):
        self.values: list = []
        self.comp = comp
        for arg in args:
            self.push(arg)

    def __str__(self):
        return f"Heap {str(self.values)}"

    def __len__(self):
        return len(self.values)

    def siftUp(self, index: int):
        while index != 0 and self.comp(self.values[index], self.values[parent := (index - 1) // 2]):
            self.values[index], self.values[parent] = self.values[parent], self.values[index]
            index = parent

    def siftDown(self, index: int):
        while (left := index * 2 + 1) < len(self.values):
            new_index = left
            if (right := left + 1) < len(self.values) and self.comp(self.values[right], self.values[left]):
                new_index = right

            if self.comp(self.values[index], self.values[new_index]):
                return

            self.values[index], self.values[new_index] = self.values[new_index], self.values[index]
            index = new_index

    def push(self, obj):
        self.values.append(obj)
        self.siftUp(len(self.values) - 1)

    def pop(self):
        if not self.values:
            raise IndexError("pop from empty heap")
        obj = self.values[0]
        self.values[0] = self.values[-1]
        del self.values[-1]
        self.siftDown(0)
        return obj

    def getRoot(self):
        if not self.values:
            raise IndexError("heap is empty")
        return self.values[0]


def siftDown(arr: list, index: int, size: int):
    while (left := index * 2 + 1) < size:
        new_index = left
        if (right := left + 1) < size and arr[right] > arr[left]:
            new_index = right

        if arr[index] > arr[new_index]:
            return

        arr[index], arr[new_index] = arr[new_index], arr[index]
        index = new_index


def heapify(arr: list):
    for i in range(len(arr) // 2 - 1, -1, -1):
        siftDown(arr, i, len(arr))


def heapSort(arr: list):
    heapify(arr)
    size = len(arr)
    for i in range(0, len(arr) - 1):
        arr[0], arr[len(arr) - 1 - i] = arr[len(arr) - 1 - i], arr[0]
        size -= 1
        siftDown(arr, 0, size)


if __name__ == "__main__":
    arr = [i % 5 for i in range(20)]
    heapSort(arr)
    print(arr)
