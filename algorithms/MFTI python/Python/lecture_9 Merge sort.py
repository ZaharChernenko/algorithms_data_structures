from random import randrange


def merge(left: list, right: list) -> list:
    temp_arr = [None] * (len(left) + len(right))
    left_i = right_i = temp_i = 0

    while left_i < len(left) and right_i < len(right):
        if left[left_i] <= right[right_i]:
            temp_arr[temp_i] = left[left_i]
            left_i += 1
            temp_i += 1
        else:
            temp_arr[temp_i] = right[right_i]
            right_i += 1
            temp_i += 1

    for i in range(left_i, len(left)):
        temp_arr[temp_i] = left[i]
        temp_i += 1
    for i in range(right_i, len(right)):
        temp_arr[temp_i] = right[i]
        temp_i += 1
    return temp_arr


def mergeSort(arr: list) -> list:
    "Сортировка слиянием"
    return arr if len(arr) <= 1 else merge(mergeSort(arr[: len(arr) // 2]), mergeSort(arr[len(arr) // 2 :]))


def partition[T](arr: list[T], left: int, right: int) -> int:
    pivot: T = arr[randrange(left, right)]
    equal_index = greater_index = left

    for index in range(left, right):
        if arr[index] < pivot:
            arr[greater_index], arr[index] = arr[index], arr[greater_index]
            arr[greater_index], arr[equal_index] = arr[equal_index], arr[greater_index]
            equal_index += 1
            greater_index += 1
        elif arr[index] == pivot:
            arr[greater_index], arr[index] = arr[index], arr[greater_index]
            greater_index += 1

    return equal_index


def _quickSort[T](arr: list[T], left: int, right: int):
    if left + 1 < right:
        sorted_index: int = partition(arr, left, right)
        _quickSort(arr, left, sorted_index)
        _quickSort(arr, sorted_index + 1, right)


def quickSort[T](arr: list[T]):
    _quickSort(arr, 0, len(arr))


def hoarSort(arr: list) -> list:
    """Более простая реализация быстрой сортировки"""
    if len(arr) <= 1:
        return arr

    pivot = arr[0]
    left, middle, right = [], [], []
    for elem in arr:
        if elem < pivot:
            left.append(elem)
        elif elem == pivot:
            middle.append(elem)
        else:
            right.append(elem)

    return hoarSort(left) + middle + hoarSort(right)


def test(func):
    print(func.__doc__)
    arr = [5, 3, 2, 4, 1]
    arr = func(arr)
    print("test #1", "ok" if arr == list(range(1, 6)) else "fail")

    arr = list(range(10, 20)) + list(range(10))
    arr = func(arr)
    print("test #2", "ok" if arr == list(range(20)) else "fail")


test(mergeSort)
test(hoarSort)
