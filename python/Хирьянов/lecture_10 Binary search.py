def binarySearch(arr: list, key) -> int:
    """Left здесь указывает на тот элемент, который гарантированно меньше, чем key,
    поэтому right необходимо найти самое первое включение key в список, если бы у нас было:
    if arr[middle] > key, то тогда правый бы гарантированно указывал на элемент, больший key, тогда бы
    left пришлось дойти до последнего включения key"""
    left = -1
    right = len(arr)

    while right - left > 1:
        middle = (left + right) // 2

        if arr[middle] < key:
            left = middle
        else:
            right = middle

    return -1 if right >= len(arr) or arr[right] != key else right


def lowerBound(arr: list, key) -> int:
    left = -1
    right = len(arr)

    while right - left > 1:

        middle = (left + right) // 2

        if arr[middle] < key:
            left = middle
        else:
            right = middle

    return right


def upperBound(arr: list, key) -> int:
    left = -1
    right = len(arr)

    while right - left > 1:

        middle = (left + right) // 2

        if arr[middle] > key:
            right = middle
        else:
            left = middle

    return right


def fib(n: int) -> int:
    f0, f1 = 0, 1
    for i in range(1, n):
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
    arr = [0, 1, 1, 2] + [0] * (n - 3)
    for i in range(4, n + 1):
        arr[i] = arr[i - 1] + arr[i - 2] + arr[i - 3]
    return arr[n]


def findWays(n: int, allowed_arr: list[bool]) -> int:
    arr = [0, 1, int(allowed_arr[2])] + [0] * (n - 2)
    for i in range(3, n + 1):
        if allowed_arr[i]:
            arr[i] = arr[i - 1] + arr[i - 2]
    return arr[n]


def countMinCost(n: int, prices_arr: list[int]):
    costs_arr = [float("inf"), prices_arr[1], prices_arr[1] + prices_arr[2]] + [0] * (n - 2)
    for i in range(3, n + 1):
        costs_arr[i] = prices_arr[i] + min(prices_arr[i - 1], prices_arr[i - 2])
    return costs_arr[n]


print(fib(8))
print(findFib(21))
print(findSol(4))
print(findWays(3, [False, True, True, True]))
