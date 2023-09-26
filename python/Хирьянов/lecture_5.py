def reverseList(l: list):
    for i in range(len(l) // 2):
        l[i], l[len(l) - 1 - i] = l[len(l) - 1 - i], l[i]


def moveLeft(l: list):
    temp = l[0]
    for i in range(len(l) - 1):
        l[i] = l[i + 1]
    l[len(l) - 1] = temp


def moveRight(l: list):
    temp = l[len(l) - 1]
    for i in range(len(l) - 1, 0, -1):
        l[i] = l[i - 1]
    l[0] = temp


def isPrime(N):
    for i in range(2, int(N ** 0.5) + 1):
        if N % i == 0:
            return False
    return True


def primesList(num: int) -> list:
    arr = [True] * (num + 1)
    for i in range(2, int(num ** 0.5) + 1):
        if arr[i]:
            for k in range(2 * i, len(arr), i):
                arr[k] = False
    for digit, is_prime in enumerate(arr):
        if is_prime: print(digit)
    return arr
