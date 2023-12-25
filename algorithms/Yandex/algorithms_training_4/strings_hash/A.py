X, HASH_CONST = 269, 2 ** 31 # на отладке использовать 10


def generatePowsArr(n) -> list:
    global X, HASH_CONST
    _pows_arr = [1] * (n + 1)  # + 1 нужно в случае того, если у нас спросят саму строку
    for i in range(1, n + 1):
        _pows_arr[i] = (_pows_arr[i - 1] * X) % HASH_CONST
    return _pows_arr


def generateHashArr(_string: str) -> list:
    global X, HASH_CONST
    hash_prefix_arr = [0] * (len(_string) + 1)
    for i in range(1, len(_string) + 1):
        hash_prefix_arr[i] = (hash_prefix_arr[i - 1] * X + (ord(_string[i - 1]) - ord('a') + 1)) % HASH_CONST
    return hash_prefix_arr


def compareSubstr(_pows_arr: list, _hash_arr: list, len_substr: int, first: int, second: int) -> str:
    global HASH_CONST
    if (_hash_arr[first + len_substr] + _hash_arr[second] * _pows_arr[len_substr]) % HASH_CONST == \
            (_hash_arr[second + len_substr] + _hash_arr[first] * _pows_arr[len_substr]) % HASH_CONST:
        return "yes"
    return "no"


"""
    ТАК ДЕЛАТЬ НЕ НАДО, РАБОТАЕТ В ДЕСЯТКИ РАЗ МЕДЛЕННЕ, ИСПОЛЬЗУЕМ ПРЕФИКС-СУММЫ !
    pows_arr = [X ** i % HASH_CONST for i in range(len(string) + 1)]
"""


string = input()
pows_arr = generatePowsArr(len(string))
hash_arr = generateHashArr(string)

n = int(input())
for i in range(n):
    print(compareSubstr(pows_arr, hash_arr, *list(map(int, input().split()))))
