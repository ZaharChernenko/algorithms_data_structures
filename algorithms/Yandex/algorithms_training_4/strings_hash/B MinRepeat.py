"""Строка S была записана много раз подряд,
после чего от получившейся строки взяли префикс и дали вам.
Ваша задача определить минимально возможную длину исходной строки S.
"""
X, HASH_CONST = 269, 2 ** 31


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


def compareSubstr(_pows_arr: list, _hash_arr: list, len_substr: int, first: int, second: int) -> bool:
    global HASH_CONST
    if (_hash_arr[first + len_substr] + _hash_arr[second] * _pows_arr[len_substr]) % HASH_CONST == \
            (_hash_arr[second + len_substr] + _hash_arr[first] * _pows_arr[len_substr]) % HASH_CONST:
        return True
    return False


def checkBase(_pows_arr: list, _hash_arr: list, str_len: int, base_len: int):
    last_step = 0
    for i in range(base_len, str_len, base_len):
        if str_len - i < base_len:
            last_step = i
            break
        if not compareSubstr(_pows_arr, _hash_arr, base_len, first=0, second=i):
            return False
    return compareSubstr(_pows_arr, _hash_arr, str_len - last_step, first=0, second=last_step)


def findStrBase(_string: str):
    _pows_arr, _hash_arr = generatePowsArr(len(string)), generateHashArr(string)
    str_len, base_len = len(_string), 1

    while base_len != str_len and not checkBase(_pows_arr, _hash_arr, str_len, base_len):
        base_len += 1
    return base_len

string = input()
print(findStrBase(string))
