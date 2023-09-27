def generateBin(length, prefix="", arr=None):
    if arr is None:
        arr = []
    if length == 0:
        print(prefix)
        arr.append(prefix)
        return
    for digit in "0", "1":
        generateBin(length - 1, prefix + digit, arr)
    return arr


def generateNumbers(length: int, base: int = 10, prefix: str = "", arr=[]):
    if length == 0:
        print(prefix)
        arr.append(prefix)
        return
    for digit in range(base):
        generateNumbers(length - 1, base, prefix + str(digit), arr)
    return arr


# в этой функции есть один косяк, который показывается лишь при неоднократном вызове функции,
# проблема в том, что по дефолту функция создает массив один раз, а при следующем вызове функции, она
# добавляет элементы в уже существующий массив, поэтому нужно либо явно указвать массив, либо сделать, как в
# функции ниже
def generatePermutationsUnexpected(length: int, elements_list: list, prefix="", arr=[]):
    assert len(elements_list) >= length, "Необходимо, чтобы число элементов было не меньше длины последовательности"
    if length == 0:
        arr.append(prefix)
        return
    for elem in elements_list:
        if str(elem) in prefix:
            continue
        generatePermutations(length - 1, elements_list, prefix + str(elem), arr)
    return arr


def generatePermutations(length: int, collection, prefix="", arr=None):
    if arr is None:
        arr = []
    assert len(collection) >= length, "Необходимо, чтобы число элементов было не меньше длины последовательности"
    if length == 0:
        arr.append(prefix)
        return
    for elem in collection:
        if str(elem) in prefix:
            continue
        generatePermutations(length - 1, collection, prefix + str(elem), arr)
    return arr


arr = generatePermutations(5, list(range(1, 6)))
print(arr)
print(len(arr))
print(generatePermutations(3, "abcdef"))
print(generatePermutations(3, "abcdef", "", []))
