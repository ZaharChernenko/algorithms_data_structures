def _genBin(prefix: list, step: int, temp_arr: list):
    if step == len(prefix):
        temp_arr.append("".join(prefix))
        return
    for digit in "01":
        prefix[step] = digit
        _genBin(prefix, step + 1, temp_arr)


def genBin(length) -> list:
    temp_arr = []
    _genBin([None] * length, 0, temp_arr)
    return temp_arr


def _genNumbers(base: int, prefix: list, step: int, temp_arr: list):
    if step == len(prefix):
        temp_arr.append("".join(map(str, prefix)))
        return

    for digit in range(base):
        prefix[step] = digit
        _genNumbers(base, prefix, step + 1, temp_arr)


def genNumbers(length: int, base: int) -> list:
    temp_arr = []
    _genNumbers(base, [None] * length, 0, temp_arr)
    return temp_arr


"""
снизу - плохой пример реализации, так как функция создает значения
по умолчанию лишь при ее определении, поэтому arr будет создан
лишь один раз, если эту функцию вызвать дважды, то она будет
содержать и значения первого вызова
"""
def generatePermutationsBad(length: int, elements_list: list, prefix="", arr=[]):
    assert len(elements_list) >= length, "Необходимо, чтобы число элементов было не меньше длины последовательности"
    if length == 0:
        arr.append(prefix)
        return
    for elem in elements_list:
        if str(elem) in prefix:
            continue
        generatePermutationsBad(length - 1, elements_list, prefix + str(elem), arr)
    return arr


def _genUniqPer(uniq: set, prefix: list, step: int, chosen: set, temp_arr: list):
    if step == len(prefix):
        temp_arr.append(list(prefix))
        return

    for elem in uniq:
        if elem in chosen:
            continue
        prefix[step] = elem
        chosen.add(elem)
        _genUniqPer(uniq, prefix, step + 1, chosen, temp_arr)
        chosen.remove(elem)


def genUniqPer(uniq: set, length: int) -> list:
    assert length <= len(uniq), "length must be not bigger than set"

    temp_arr = []
    _genUniqPer(uniq, [None] * length, 0, set(), temp_arr)
    return temp_arr


def Dec(arr, i=0, a=None, prefix=None):
    if i == len(arr):
        a.append(tuple(prefix))
        return
    if a is None:
        a = []
    if prefix is None:
        prefix = []
    for j in range(len(arr[i])):
        Dec(arr, i + 1, a, prefix + [arr[i][j]])
    return a


def _genDecart(arr2d: list[list], prefix, step: int, temp_arr: list):
    if step == len(arr2d):
        "important to copy prefix, because its mutable"
        temp_arr.append(list(prefix))
        return

    for number in arr2d[step]:
        prefix[step] = number
        _genDecart(arr2d, prefix, step + 1, temp_arr)


def genDecart(arr2d: list[list]) -> list[list]:
    temp_arr = []
    _genDecart(arr2d, [None] * len(arr2d), 0, temp_arr)
    return temp_arr


for vector in genDecart([[1, 2, 3], [4, 5, 6], [7, 8, 9]]):
    print(vector)


print(genBin(3))
