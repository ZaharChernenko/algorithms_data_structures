import timeit
from queue import Queue

from BinaryTree import BinaryTree
from MyQueue import MyQueue


def timer(func, *args, **kwargs):
    """measures the time of one function call"""

    start = timeit.time.time_ns()
    func(*args, **kwargs)
    elapsed = timeit.time.time_ns() - start
    print(f"Время выполнения в ns: {elapsed:,d}")


def timerRepeat(func, repeat: int, *args, **kwargs):
    start = timeit.time.time_ns()
    for _ in range(repeat):
        func(*args, **kwargs)
    elapsed = timeit.time.time_ns() - start
    print(f"Время выполнения в ns: {elapsed:,d}")
    return elapsed


def bestOf(func, repeat: int, *args, **kwargs):
    fastest_run = float("inf")
    for _ in range(repeat):
        start = timeit.time.time_ns()
        func(*args, **kwargs)
        elapsed = timeit.time.time_ns() - start
        fastest_run = min(fastest_run, elapsed)
    print(f"Самое быстрое время в ns: {fastest_run:,}")
    return fastest_run


def bestOfTotal(func, repeat: int, loops: int, *args, **kwargs):
    fastest_run = float("inf")
    for _ in range(repeat):
        elapsed = timerRepeat(func, loops, *args, **kwargs)
        fastest_run = min(fastest_run, elapsed)
    print(f"{loops} циклов, лучшее время из {repeat} в ns: {fastest_run:,d}")


# timer(MyQueue, 1, 2, 3, 4, 5)
# timerRepeat(MyQueue, 1000, 1, 2, 3, 4, 5)
# bestOf(MyQueue, 100, 1, 2, 3, 4, 5, 6)
# bestOfTotal(MyQueue, 10, 1000, 1, 2, 3, 4, 5)
# print(min(timeit.repeat(repeat=10, number=1000, stmt="MyQueue(1, 2, 3, 4, 5)", setup="from MyQueue import MyQueue")))
# print(min(timeit.repeat(repeat=10, number=1000, stmt="MyQueue(1, 2, 3, 4, 5)", globals=globals())))
# с globals не работает нижняя команда
# python3 -m timeit "$(cat main.py)"


q = MyQueue(1, 2, 3, 4, 5)
for elem in q:
    elem = 2
print(q)

q = Queue()
print(dir(q))
