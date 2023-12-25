from math import floor
X, HASH_CONST = 1013, 2 ** 31 # на отладке использовать 10


def generatePowsArr(n) -> list:
    global X, HASH_CONST
    _pows_arr = [1] * (n + 1)  # + 1 нужно в случае того, если у нас спросят саму строку
    for i in range(1, n + 1):
        _pows_arr[i] = (_pows_arr[i - 1] * X) % HASH_CONST
    return _pows_arr

fdsf
def generateHashArr(obj) -> list:
    global X, HASH_CONST
    hash_prefix_arr = [0] * (len(obj) + 1)
    for i in range(1, len(obj) + 1):
        hash_prefix_arr[i] = (hash_prefix_arr[i - 1] * X + obj[i - 1]) % HASH_CONST
    return hash_prefix_arr


def compareSubstr(_pows_arr: list, _hash_arr: list, len_substr: int, first: int, second: int) -> str:
    global HASH_CONST
    if (_hash_arr[first + len_substr] + _hash_arr[second] * _pows_arr[len_substr]) % HASH_CONST == \
            (_hash_arr[second + len_substr] + _hash_arr[first] * _pows_arr[len_substr]) % HASH_CONST:
        return "yes"
    return "no"


n_cubes_seen, n_colors = map(int, input().split())
cubes_seen_arr = list(map(int, input().split()))
print(len(cubes_seen_arr))
pows_arr = generatePowsArr(n_cubes_seen)

hash_arr_straight = generateHashArr(cubes_seen_arr)
hash_arr_reversed = generateHashArr(cubes_seen_arr[::-1])

for mirror_delimiter in range(floor(len(cubes_seen_arr) / 2), -1, -1):
    if (hash_arr_straight[mirror_delimiter * 2] + hash_arr_reversed[len(cubes_seen_arr) - mirror_delimiter] * pows_arr[mirror_delimiter]) % HASH_CONST == \
            (hash_arr_reversed[len(cubes_seen_arr)] +
             hash_arr_straight[mirror_delimiter] * pows_arr[mirror_delimiter]) % HASH_CONST:
        print(n_cubes_seen - mirror_delimiter, end=" ")

