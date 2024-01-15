from __future__ import annotations

from SingleLinkedList import SingleLinkedList


class Set:
    def __init__(self, *args):
        self._n_buckets: int = 10
        self._capacity: int = 40 // 3
        self._size = 0
        self._buckets: list[SingleLinkedList] = [SingleLinkedList() for _ in range(self._n_buckets)]

        for arg in args:
            self.add(arg)

    def __len__(self):
        return self._size

    def __contains__(self, obj):
        return obj in self._buckets[hash(obj) % self._n_buckets]

    def _rehash(self):
        self._n_buckets *= 2
        self._capacity = 4 * self._n_buckets // 3
        temp_bucket: list[SingleLinkedList] = [SingleLinkedList() for _ in range(self._n_buckets)]

        for bucket in self._buckets:
            while bucket:
                elem = bucket.popFront()
                temp_bucket[hash(elem) % self._n_buckets].pushBack(elem)

        self._buckets = temp_bucket

    def add(self, obj):
        index: int = hash(obj) % self._n_buckets

        if obj in self._buckets[index]:
            return

        self._buckets[index].pushBack(obj)
        self._size += 1
        if self._size == self._capacity:
            self._rehash()

    def remove(self, obj):
        index: int = hash(obj) % self._n_buckets

        try:
            self._buckets[index].remove(obj)
        except IndexError:
            raise KeyError(f"KeyError: {obj}")
        else:
            self._size -= 1

    def discard(self, obj):
        index: int = hash(obj) % self._n_buckets

        try:
            self._buckets[index].remove(obj)
        except IndexError:
            pass
        else:
            self._size -= 1

    def printBuckets(self):
        for i, bucket in enumerate(self._buckets):
            print(f"Bucket №{i}: {bucket}")


if __name__ == "__main__":
    uniq = Set(*range(100))

    for i in range(len(uniq)):
        uniq.remove(i)
    for j in range(100):
        uniq.add([])
    uniq.printBuckets()
