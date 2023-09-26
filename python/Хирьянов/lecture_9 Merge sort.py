def merge(left_arr: list, right_arr: list):
    result_arr = []
    left_arr_index = right_arr_index = 0

    while left_arr_index < len(left_arr) and right_arr_index < len(right_arr):
        if left_arr[left_arr_index] <= right_arr[right_arr_index]:
            result_arr.append(left_arr[left_arr_index])
            left_arr_index += 1
        else:
            result_arr.append(right_arr[right_arr_index])
            right_arr_index += 1

    return result_arr + left_arr[left_arr_index:] + right_arr[right_arr_index:]


def mergeSort(arr: list) -> list:
    """Сортировка слиянием"""
    if len(arr) <= 1:
        return arr
    return merge(mergeSort(arr[:len(arr) // 2]), mergeSort(arr[len(arr) // 2:]))


def hoarSort(arr: list) -> list:
    """Сортировка Тони Хоара"""
    if len(arr) <= 1:
        return arr

    barrier = arr[0]
    left = []
    middle = []
    right = []

    for elem in arr:
        if elem < barrier:
            left.append(elem)
        elif elem == barrier:
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
