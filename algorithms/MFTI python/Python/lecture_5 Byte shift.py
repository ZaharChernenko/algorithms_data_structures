def reverseList(arr: list) -> list:
    """
    function that returns reversed list
    >>> reverseList([5, 4, 3, 2, 1])
    [1, 2, 3, 4, 5]
    """
    assert isinstance(arr, list), "arr, must be type list"
    temp_arr = arr[:]
    for i in range(len(arr) // 2):
        temp_arr[i], temp_arr[len(arr) - 1 - i] = temp_arr[len(arr) - 1 - i], temp_arr[i]
    return temp_arr


def moveLeft(arr: list) -> list:
    """
    function that returns arr shifted to left
    >>> moveLeft([1, 2, 3])
    [2, 3, 1]
    >>> moveLeft([1])
    [1]
    """
    assert isinstance(arr, list), "arr must be type list"
    shifted_arr = arr[:]
    stash = arr[0]

    for i in range(len(arr) - 1):
        shifted_arr[i] = shifted_arr[i + 1]
    shifted_arr[-1] = stash
    return shifted_arr


def moveRight(arr: list) -> list:
    """
    function that returns arr shifted to right
    >>> moveRight([1, 2, 3])
    [3, 1, 2]
    """
    assert isinstance(arr, list), "arr must be type list"
    shifted_arr = arr[:]
    stash = arr[-1]

    for i in range(len(arr) - 2, -1, -1):
        shifted_arr[i + 1] = shifted_arr[i]
    shifted_arr[0] = stash
    return shifted_arr


def isPrime(num: int) -> bool:
    assert isinstance(num, int), "number must be integer"

    for delimeter in range(2, int(num**0.5) + 1):
        if not num % delimeter:
            return False
    return True


def primesList(upper_bound: int) -> list[int]:
    primes_list: list[int] = [True] * (upper_bound + 1)
    primes_list[0] = primes_list[1] = False

    for i in range(2, int(len(primes_list) ** 0.5) + 1):
        if primes_list[i]:
            for j in range(i**2, len(primes_list), i):  # число со вторым множителем, меньшим чем i уже отсеялось
                primes_list[j] = False

    return [num for num in range(upper_bound + 1) if primes_list[num]]


if __name__ == "__main__":
    import doctest

    doctest.testmod(verbose=True)
    print(primesList(1000))
