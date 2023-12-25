from random import randrange


def partition(arr: list, left: int, right: int) -> int:
    equal = greater = left  # equal - pointer to first equal, greater - pointer to first greater
    pivot = arr[randrange(left, right)]

    for i in range(left, right):
        if arr[i] < pivot:
            arr[i], arr[greater] = arr[greater], arr[i]  # i только один раз
            arr[greater], arr[equal] = arr[equal], arr[greater]
            equal += 1
            greater += 1

        elif arr[i] == pivot:
            arr[i], arr[greater] = arr[greater], arr[i]
            greater += 1

    return equal  # удобнее возвращать для k порядковой статистики, потому что greater может быть неупорядочен


def __quickSort(arr: list, left: int, right: int) -> None:
    if left < right:
        sorted_elem_index = partition(arr, left, right)  # этот индекс будет на том же месте в упорядоченном arr
        __quickSort(arr, left, sorted_elem_index)
        __quickSort(arr, sorted_elem_index + 1, right)


def quickSort(arr: list) -> None:
    __quickSort(arr, 0, len(arr))


def kOrdinal(arr: list, k: int):
    left, right = 0, len(arr)
    while (sorted_elem_index := partition(arr, left, right)) != k:
        if sorted_elem_index < k:
            left = sorted_elem_index + 1
        else:
            right = sorted_elem_index
    return arr[sorted_elem_index]


# user_arr = list(map(int, input().split()))
user_arr = [0, 1, 1, 3, 2, 4, 5, -1]
print(kOrdinal(user_arr, 3))
