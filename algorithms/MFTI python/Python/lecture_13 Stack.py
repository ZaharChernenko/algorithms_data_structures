"""
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
            if not stack or tokens[stack.pop()] != elem:
                return False
    return len(stack) == 0


if __name__ == "__main__":
    import doctest
    doctest.testmod()
