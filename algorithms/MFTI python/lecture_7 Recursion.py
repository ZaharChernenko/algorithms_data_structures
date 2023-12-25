def matreshka(n):
    if n == 0:
        print("Матрешечка")
        return
    else:
        print(f"Верх матрешки: {n}")
        matreshka(n - 1)
        print(f"Низ матрешки: {n}")


def runFractal():
    import graphics as gr

    def fractal(pA, pB, pC, pD, alpha, deep: int, window):
        assert deep >= 0, "deep must be non-negative"

        if deep == 0:
            return

        new_points = []
        for x, y in (pA, pB), (pB, pC), (pC, pD), (pD, pA):
            gr.Line(gr.Point(*x), gr.Point(*y)).draw(window)
            new_points.append((x[0] * (1 - alpha) + y[0] * alpha, x[1] * (1 - alpha) + y[1] * alpha))
        fractal(*new_points, alpha, deep - 1, window)

    window = gr.GraphWin("Fractal", 700, 700)
    fractal((100, 100), (600, 100), (600, 600), (100, 600), alpha=0.2, deep=20, window=window)
    input()


def myPow(num, degree: int):
    """
    >>> myPow(2, 2)
    4
    >>> myPow(2, 5)
    32
    """
    assert degree >= 0, "degree must be non-negative"

    if degree == 0:
        return 1
    return myPow(num, degree - 1) * num


def fastPow(num, degree: int):
    """
    >>> fastPow(2, 2)
    4
    >>> fastPow(2, 5)
    32
    """
    assert degree >= 0, "degree must be non-negative"

    if degree == 0:
        return 1
    return fastPow(num * num, degree // 2) if degree % 2 == 0 else fastPow(num, degree - 1) * num


def gcd(a, b):
    """
    >>> gcd(10, 12)
    2
    >>> gcd(120, 12)
    12
    """
    if a == b:
        return a
    return gcd(a - b, b) if a > b else gcd(a, b - a)


def fasterGCD(a, b):
    """
    >>> fasterGCD(10, 210)
    10
    """
    return a if b == 0 else fasterGCD(b, a % b)


if __name__ == "__main__":
    import doctest
    doctest.testmod()

