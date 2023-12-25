"""
>>> changeBase("111", 10, 2)
'7'
>>> changeBase("FF", 10, 16)
'255'
>>> changeBase("256", 16)
'100'
"""


decode_to10_dict = {str(i): i for i in range(10)}
decode_to10_dict.update({"A": 10, "B": 11, "C": 12, "D": 13, "E": 14, "F": 15})


def convertToDecimal(num: str, cur_base: int) -> int:
    """function converts number to decimal base"""
    res = 0
    for elem in num:
        res *= cur_base
        res += decode_to10_dict[elem]
    return res


def changeBase(num: str, wanted_base: int=2, cur_base: int=10) -> str:
    """function converts number from one base to another"""
    assert isinstance(num, str), "number must be str type"
    if cur_base != 10:
        num = convertToDecimal(num, cur_base)
    else:
        num = int(num)

    res = []
    while num > 0:
        res.append(num % wanted_base)
        num //= wanted_base
    return "".join(map(str, res[::-1]))


if __name__ == "__main__":
    import doctest
    doctest.testmod()

"""Такие алгоритмы как, поиск числа, сумма, произведение, максимум, минимум, подсчет числа элементов
то есть когда из последовательности генерируется одно число или когда из одного числа генерируется последовательность
являются однопроходными"""
