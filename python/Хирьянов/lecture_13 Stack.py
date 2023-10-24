"""
здесь можно писать то, что ожидается от выполнения кода, главное импортировать библиотеку doctest
https://ru.hexlet.io/courses/advanced_python/lessons/python-doctest/theory_unit
>>> s = [34]
>>> s
[34]
>>> s.append(12)
>>> s
[34, 12]
>>> validExp("()")
True
>>> validExp("(")
False
>>> validExp("(())")
True
>>> validExp1("(]")
False
>>> validExp1("([{}])")
True
"""


def validExp(exp: str) -> bool:
    count_braces = 0
    for elem in exp:
        if elem == "(":
            count_braces += 1
        elif elem == ")":
            count_braces -= 1
            if count_braces < 0:
                return False
    return count_braces == 0


def validExp1(exp: str) -> bool:
    tokens = {"(": ")", "[": "]", "{": "}"}
    stack = []
    for elem in exp:
        if elem in tokens:
            stack.append(elem)
        elif elem in ")]}":
            if tokens[stack.pop()] != elem:
                return False
    return len(stack) == 0


if __name__ == "__main__":  # запускает этот код, только если этот файл запущен, как основной, если же он
    # импортируется, то этот код не запустится
    # https://habr.com/ru/articles/702218/
    import doctest

    doctest.testmod()
