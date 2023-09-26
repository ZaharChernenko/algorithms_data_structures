import time
def insertSort(arr: list) -> list:
    """Сортировка вставками"""
    temp_arr = arr[:]
    for top in range(1, len(temp_arr)):
        i = top
        while i > 0 and temp_arr[i] < temp_arr[i - 1]:
            temp_arr[i], temp_arr[i - 1] = temp_arr[i - 1], temp_arr[i]
            i -= 1
    return temp_arr


def choiceSort(arr: list) -> list:
    """Сортировка выбором"""
    temp_arr = arr[:]
    for pos in range(len(temp_arr) - 1):
        for i in range(pos + 1, len(temp_arr)):
            if temp_arr[i] < temp_arr[pos]:
                temp_arr[i], temp_arr[pos] = temp_arr[pos], temp_arr[i]
    return temp_arr


def bubbleSort(arr: list) -> list:
    """Сортировка пузырьком"""
    temp_arr = arr[:]
    for bypass in range(len(temp_arr) - 1):
        for i in range(1, len(temp_arr) - bypass):
            if temp_arr[i] < temp_arr[i - 1]:
                temp_arr[i], temp_arr[i - 1] = temp_arr[i - 1], temp_arr[i]
    return temp_arr


def countSort(arr: list) -> list:
    """Сортировка подсчетом"""
    count_arr = [0] * (max(arr) + 1)
    for elem in arr:
        count_arr[elem] += 1
    new_arr = []
    for i in range(len(count_arr)):
        new_arr += [i] * count_arr[i]
    return new_arr


def test(func):
    print(func.__doc__)

    arr = [5, 3, 4, 2, 1]
    arr = func(arr)
    print("test #1:", "ok" if arr == list(range(1, 6)) else "false")

    arr = list(range(10, 2000)) + list(range(10))
    arr = func(arr)
    print("test #1:", "ok" if arr == list(range(2000)) else "false")


start = time.time_ns()
test(insertSort)
print(time.time_ns() - start)


start = time.time_ns()
test(choiceSort)
print(time.time_ns() - start)

start = time.time_ns()
test(bubbleSort)
print(time.time_ns() - start)

start = time.time_ns()
test(countSort)
print(time.time_ns() - start)