def insertSort(arr: list) -> list:
    """Сортировка вставками"""
    temp_arr = arr[:]

    for top in range(1, len(arr)):
        i = top
        while i > 0 and temp_arr[i - 1] > temp_arr[i]:
            temp_arr[i - 1], temp_arr[i] = temp_arr[i], temp_arr[i - 1]
            i -= 1
    return temp_arr


def choiceSort(arr: list) -> list:
    """Сортировка выбором"""
    temp_arr = arr[:]

    for pos in range(len(arr) - 1):
        for i in range(pos + 1, len(arr)):
            if temp_arr[pos] > temp_arr[i]:
                temp_arr[pos], temp_arr[i] = temp_arr[i], temp_arr[pos]
    return temp_arr


def bubbleSort(arr: list) -> list:
    """Сортировка пузырьком"""
    temp_arr = arr[:]

    for bypass in range(len(arr) - 1):
        for i in range(1, len(arr) - bypass):
            if temp_arr[i - 1] > temp_arr[i]:
                temp_arr[i - 1], temp_arr[i] = temp_arr[i], temp_arr[i - 1]
    return temp_arr


def bubbleSortCheck(arr: list) -> list:
    """Сортировка пузырьком с проверкой на упорядоченность"""
    temp_arr = arr[:]

    for bypass in range(len(arr) - 1):
        is_sorted = True
        for i in range(1, len(arr) - bypass):
            if temp_arr[i - 1] > temp_arr[i]:
                temp_arr[i - 1], temp_arr[i] = temp_arr[i], temp_arr[i - 1]
                is_sorted = False
        if is_sorted:
            break
    return temp_arr


def countSort(arr: list) -> list:
    """Сортировка подсчетом"""
    size = max(arr) + 1
    count_arr = [0] * size
    pos_arr = [0] * size

    for elem in arr:
        count_arr[elem] += 1
    for i in range(1, size):
        pos_arr[i] = pos_arr[i - 1] + count_arr[i - 1]

    temp_arr = [0] * len(arr)
    for elem in arr:
        temp_arr[pos_arr[elem]] = elem
        pos_arr[elem] += 1
    return temp_arr


def test(func):
    import time
    print(func.__doc__)
    start = time.time_ns()

    arr = [5, 3, 4, 3, 2, 1]
    print("test №1: " "ok" if func(arr) == [1, 2, 3, 3, 4, 5] else "fail")

    arr = list(range(10, 2000)) + list(range(10))
    print("test №2: " "ok" if func(arr) == list(range(2000)) else "fail")

    arr = [1] * 2000
    print("test №3: " "ok" if func(arr) == arr else "fail")

    print(time.time_ns() - start, '\n')


test(insertSort)
test(choiceSort)
test(bubbleSort)
test(bubbleSortCheck)
test(countSort)
test(sorted)
