import time


def insertSort(vec: list) -> list:
    """Сортировка вставками"""
    sorted_vec: list = vec[:]
    for top in range(1, len(vec)):
        i = top
        while i > 0 and sorted_vec[i - 1] > sorted_vec[i]:
            sorted_vec[i - 1], sorted_vec[i] = sorted_vec[i], sorted_vec[i - 1]
            i -= 1
    return sorted_vec


def choiceSort(vec: list) -> list:
    """Сортировка выбором"""
    sorted_vec: list = vec[:]
    for pos in range(0, len(vec) - 1):
        for i in range(pos + 1, len(vec)):
            if sorted_vec[pos] > sorted_vec[i]:
                sorted_vec[pos], sorted_vec[i] = sorted_vec[i], sorted_vec[pos]
    return sorted_vec


def bubbleSort(vec: list) -> list:
    """Сортировка пузырьком"""
    sorted_vec: list = vec[:]
    for bypass in range(0, len(vec) - 1):
        for i in range(1, len(vec) - bypass):
            if sorted_vec[i - 1] > sorted_vec[i]:
                sorted_vec[i], sorted_vec[i - 1] = sorted_vec[i - 1], sorted_vec[i]
    return sorted_vec


def bubbleSortCheck(vec: list) -> list:
    """Сортировка пузырьком с проверкой на упорядоченность"""
    sorted_vec: list = vec[:]
    for bypass in range(len(vec) - 1):
        is_sorted: bool = True
        for i in range(1, len(vec) - bypass):
            if sorted_vec[i] < sorted_vec[i - 1]:
                sorted_vec[i], sorted_vec[i - 1] = sorted_vec[i - 1], sorted_vec[i]
                is_sorted = False
        if is_sorted: return sorted_vec
    return sorted_vec


def pythonCountSort(vec: list) -> list:
    """Сортировка подсчетом"""
    count_arr: list = [0] * (max(vec) + 1)
    for elem in vec:
        count_arr[elem] += 1
    sorted_vec: list = []
    for i in range(len(count_arr)):
        sorted_vec.extend([i] * count_arr[i]) # так можно, но медленнее sorted_vec += [i] * count_arr[i]
    return sorted_vec


def countSort(vec: list) -> list:
    """Универсальная сортировка подсчетом"""
    max_elem: int = max(vec)
    count_vec, pos_vec = [0] * (max_elem + 1), [0] * (max_elem + 1)

    for elem in vec:
        count_vec[elem] += 1
    for i in range(1, len(pos_vec)):
        pos_vec[i] = pos_vec[i - 1] + count_vec[i - 1]

    sorted_vec: list = [0] * len(vec)
    for elem in vec:
        sorted_vec[pos_vec[elem]] = elem
        pos_vec[elem] += 1
    return sorted_vec


def test(func):
    print(func.__doc__)

    start = time.time_ns()
    arr = [5, 3, 4, 2, 1]
    arr = func(arr)
    print("test #1:", "ok" if arr == list(range(1, 6)) else "false")

    arr = list(range(1000, 2000)) + list(range(10)) + list(range(10, 1000))
    print("test #2:", "ok" if list(range(2000)) == func(arr) else "false")

    arr = [1] * 2000
    arr = func(arr)
    print("test #3:", "ok" if arr == func(arr) else "false")

    print(f"{(time.time_ns() - start):,}", '\n')


test(insertSort)
test(choiceSort)
test(bubbleSort)
test(bubbleSortCheck)
test(pythonCountSort)
test(countSort)
test(sorted)
