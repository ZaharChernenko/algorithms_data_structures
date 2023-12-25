"""
>>> arr = [1, 2, 3]
>>> reverseList(arr)
[3, 2, 1]
>>> arr.append(23)
>>> reverseList(arr)
[23, 3, 2, 1]
>>> arr
[1, 2, 3, 23]
>>> moveLeft(arr)
[2, 3, 23, 1]
>>> moveRight(arr)
[23, 1, 2, 3]
"""


def reverseList(arr: list) -> list:
    """function that returns reversed list
    >>> reverseList([5, 4, 3, 2, 1])
    [1, 2, 3, 4, 5]
    """
    assert isinstance(arr, list), "arr, must be type list"
    temp_arr = arr[:]
    for i in range(len(arr) // 2):
        temp_arr[i], temp_arr[len(arr) - 1 - i] = temp_arr[len(arr) - 1 - i], temp_arr[i]
    return temp_arr


def moveLeft(arr: list) -> list:
    """function that returns arr shifted to left"""
    assert isinstance(arr, list), "arr must be type list"
    temp_arr = arr[:]
    stash = arr[0]

    for i in range(len(arr) - 1):
        temp_arr[i] = temp_arr[i + 1]
    temp_arr[-1] = stash
    return temp_arr


def moveRight(arr: list) -> list:
    """function that returns arr shifted to right"""
    assert isinstance(arr, list), "arr must be type list"
    temp_arr = arr[:]
    stash = arr[-1]

    for i in range(len(arr) - 1, 0, -1):
        temp_arr[i] = temp_arr[i - 1]
    temp_arr[0] = stash
    return temp_arr


def isPrime(num: int):
    assert isinstance(num, int), "number must be integer"

    for i in range(2, int(num ** 0.5) + 1):
        if num % i == 0:
            return False
    return True


def primesList(num: int) -> list:
    assert isinstance(num, int), "number must be integer"

    arr = [True] * (num + 1)
    for i in range(2, int(num ** 0.5) + 1):
        if arr[i]:
            for k in range(2 * i, len(arr), i):
                arr[k] = False
    for digit, is_prime in enumerate(arr):
        if is_prime:
            print(digit)
    return arr


if __name__ == "__main__":
    import doctest
    doctest.testmod(verbose=True)
