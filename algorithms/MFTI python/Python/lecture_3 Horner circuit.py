hex2decimal = {str(i): i for i in range(10)}
hex2decimal.update({"A": 10, "B": 11, "C": 12, "D": 13, "E": 14, "F": 15})
decimal2hex = {hex2decimal[key]: key for key in hex2decimal}


def convert2Decimal(num: str, cur_base: int) -> int:
    """
    function converts number to decimal base
    >>> convert2Decimal("FF", 16)
    255
    >>> convert2Decimal("1000", 2)
    8
    >>> convert2Decimal("321", 4)
    57
    """
    res = 0
    for elem in num:
        res *= cur_base
        res += hex2decimal[elem]
    return res


def changeBase(num_str: str, wanted_base: int = 2, cur_base: int = 10) -> str:
    """
    function converts number from one base to another
    >>> changeBase("111", 10, 2)
    '7'
    >>> changeBase("FF", 10, 16)
    '255'
    >>> changeBase("256", 16)
    '100'
    """
    assert isinstance(num_str, str), "number must be str type"
    if cur_base != 10:
        num = convert2Decimal(num_str, cur_base)
    else:
        num = int(num_str)

    res = []
    while num > 0:
        res.append(decimal2hex[num % wanted_base])
        num //= wanted_base
    return "".join(reversed(res))


if __name__ == "__main__":
    import doctest

    doctest.testmod()

"""Такие алгоритмы как, поиск числа, сумма, произведение, максимум, минимум, подсчет числа элементов
то есть когда из последовательности генерируется одно число или когда из одного числа генерируется последовательность
являются однопроходными"""
