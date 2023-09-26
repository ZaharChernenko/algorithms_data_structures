import graphics as gr
import time


def matreshka(n):
    if n == 0:
        print("Матрешечка")
        return
    else:
        print(f"Верх матрешки: {n}")
        matreshka(n - 1)
        print(f"Низ матрешки: {n}")


window = gr.GraphWin("Fractal rectangle", 600, 600)


def fractal(A, B, C, D, alpha = 0.1, deep = 10):
    if deep == 0:
        return
    new_fractal = []
    for p1, p2 in (A, B), (B, C), (C, D), (D, A):
        graphics.Line(graphics.Point(*p1), graphics.Point(*p2)).draw(window)
        new_fractal.append((p1[0] * (1- alpha) + p2[0] * alpha, p1[1] * (1 - alpha) + p2[1] * alpha))
    fractal(*new_fractal, alpha, deep - 1)


fractal((100, 100), (500, 100), (500, 500), (100, 500))


def factorize(n: int):
    assert n >= 0, "number must be non negative"
    if n == 1 or n == 0:
        return 1
    else:
        return n * factorize(n - 1)


def searchGCD(a, b):
    if a == b:
        return a
    if a > b:
        return searchGCD(b, a - b)
    else:
        return searchGCD(a, b - a)


def fasterGCD(a, b):
    return a if b == 0 else fasterGCD(b, a % b)


def fastPow(num: float, pow: int):
    assert pow >= 0, "pow must be not negative"
    if pow == 0:
        return 1
    return fastPow(num ** 2, pow // 2) if pow % 2 == 0 else fastPow(num, pow - 1) * num


start = time.time_ns()
print(fastPow(2, 10))
print(time.time_ns() - start)
