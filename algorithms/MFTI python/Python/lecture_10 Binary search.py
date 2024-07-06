def binarySearch[T](arr: list[T], val: T) -> int:
    left, right = -1, len(arr)

    while left + 1 < right:
        middle: int = (left + right) >> 1
        if arr[middle] < val:
            left = middle
        else:
            right = middle

    return -1 if right == len(arr) or arr[right] != val else right


def lowerBound[T](arr: list[T], val: T) -> int:
    """Возвращает индекс первого элемента, который либо больше val,
    либо равен ему (первый индекс для вставки в отсортированном массиве)"""
    left, right = -1, len(arr)

    while left + 1 < right:
        middle: int = (left + right) >> 1
        if arr[middle] < val:
            left = middle
        else:
            right = middle
    return right


def upperBound[T](arr: list[T], val: T) -> int:
    """Возвращает индекс первого элемента, который строго больше val,
    (последний индекс для вставки в отсортированный массив)"""
    left, right = -1, len(arr)

    while left + 1 < right:
        middle: int = (left + right) >> 1
        if arr[middle] > val:
            right = middle
        else:
            left = middle

    return right


def count(arr: list, key) -> int:
    return upperBound(arr, key) - lowerBound(arr, key)


def fib(n: int) -> int:
    f0, f1 = 0, 1
    for _ in range(1, n):
        f0, f1 = f1, f0 + f1
    return f1


def findFib(n: int) -> int:
    f0, f1 = 0, 1
    i = 1
    while n > f1:
        f0, f1 = f1, f0 + f1
        i += 1

    return i if n == f1 else -1


def findSol(n: int) -> int:
    count_arr: list[int] = [0] * (n + 1)
    count_arr[1] = 1
    for i in range(2, n + 1):
        count_arr[i] = count_arr[i - 1] + count_arr[i - 2]

    return count_arr[n]


def findWays(n: int, allowed_arr: list[bool]) -> int:
    arr = [0, 1, int(allowed_arr[2])] + [0] * (n - 2)
    for i in range(3, n + 1):
        if allowed_arr[i]:
            arr[i] = arr[i - 1] + arr[i - 2]
    return arr[n]


def countMinCost(n: int, prices_arr: list[int]):
    costs_arr = [float("inf"), prices_arr[1], prices_arr[1] + prices_arr[2]] + [0] * (n - 2)
    for i in range(3, n + 1):
        costs_arr[i] = prices_arr[i] + min(costs_arr[i - 1], costs_arr[i - 2])
    return costs_arr[n]


print(findSol(5))
print(findSol(4))
print(findWays(3, [False, True, True, True]))
