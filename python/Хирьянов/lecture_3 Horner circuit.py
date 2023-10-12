def convertToAnotherNumberSystem(num: str, num_base: int = 10, wanted_base: int = 10):
    if num_base != 10:
        num_decimal = 0
        for number in num:
            num_decimal *= num_base
            num_decimal += int(number, base=num_base)
    else:
        num_decimal = int(num)

    res = []
    while num_decimal > 0:
        res.append(str(num_decimal % wanted_base))
        num_decimal //= wanted_base
    return "".join(res[::-1])


print(convertToAnotherNumberSystem("12", 10, 10))


def convertToAnotherSystem(num: str, cur_base: int, want_base: int):
    num_decimal = 0
    for elem in num:
        num_decimal *= cur_base
        num_decimal += int(elem, base=cur_base)
    res = ""
    while num_decimal > 0:
        res += str(num_decimal % want_base)
        num_decimal //= want_base
    return res[::-1]


print(convertToAnotherSystem("f2", 16, 10))
"""Такие алгоритмы как, поиск числа, сумма, произведение, максимум, минимум, подсчет числа элементов
то есть когда из последовательности генерируется одно число или когда из одного числа генерируется последовательность
являются однопроходными"""
