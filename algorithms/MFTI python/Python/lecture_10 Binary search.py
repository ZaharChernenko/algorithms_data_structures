def binarySearch(arr: list, key):
    left, right = -1, len(arr)
    while left < right - 1:
        middle = (left + right) // 2
        if arr[middle] < key:
            left = middle
        else:
            right = middle
    return -1 if right == len(arr) or arr[right] != key else right


def lowerBound(arr: list, key) -> int:
    left, right = -1, len(arr)

    while left < right - 1:
        middle = (left + right) // 2
        if arr[middle] < key:
            left = middle
        else:
            right = middle
    return right


def upperBound(arr: list, key) -> int:
    left, right = -1, len(arr)

    while left < right - 1:
        middle = (left + right) // 2
        if arr[middle] <= key:
            left = middle
        else:
            right = middle
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
    count_arr = [0, 1, 1] + [0] * (n - 2)
    for i in range(3, n + 1):
        count_arr[i] = count_arr[i - 1] + count_arr[i - 2] + count_arr[i - 3]
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


print(findSol(4))
print(findWays(3, [False, True, True, True]))

test_arr = [i for i in range(10) for _ in range(i)]
print(test_arr)
print(count(test_arr, 9))
