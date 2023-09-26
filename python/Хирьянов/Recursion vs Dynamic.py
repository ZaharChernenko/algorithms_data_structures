from functools import lru_cache
import time

def recFib(n):
    if n <= 2:
        return 1
    return recFib(n - 1) + recFib(n - 2)


@lru_cache(256)
def cacheRecFib(n):
    if n <= 2:
        return 1
    return cacheRecFib(n - 1) + cacheRecFib(n - 2)

def dynamicFib(n):
    f0, f1 = 0, 1
    for i in range(1, n):
        f0, f1 = f1, f1 + f0
    return f1


start = time.time_ns()
print(recFib(35), time.time_ns() - start)

start = time.time_ns()
print(cacheRecFib(35), time.time_ns() - start)

start = time.time_ns()
print(dynamicFib(35), time.time_ns() - start)
# динамическое вычисление работает в несколько раз быстрее, даже чем функция с кэшем
