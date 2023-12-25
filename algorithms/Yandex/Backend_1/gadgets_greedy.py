"""Вася подсчитал, что у него есть m гаджетов, которые нужно подключить к USB и всего n USB-портов на компьютере.
В ближайшем интернет-магазине продаются разветвители с одного USB на два за c2 рублей и
USB-хабы с одного USB на 5 по c5 рублей.
Разветвители и хабы можно подключать друг к другу и к USB-портам компьютера.
Определите, какое минимальное количество рублей нужно потратить Васе, чтобы подключить все USB устройства.
При этом можно обеспечить возможность подключить и больше
m гаджетов, главное минимизировать цену."""
import math

n = int(input())
m = int(input())
c2 = int(input())
c5 = int(input())


def findMinCost(ports_num, gadgets_num, cost2, cost5):
    diff = gadgets_num - ports_num
    if diff <= 0:
        return 0

    if cost5 <= cost2:
        return math.ceil(diff / 4) * cost5

    if cost2 * 4 <= cost5:
        return diff * cost2

    sum5 = diff // 4 * cost5
    if diff % 4 == 1:
        return sum5 + cost2

    if diff % 4 == 2:
        if cost2 * 2 <= cost5:
            return sum5 + cost2 * 2
        return sum5 + cost5

    if diff % 4 == 3:
        if cost2 * 3 <= cost5:
            return sum5 + cost2 * 3
        return sum5 + cost5

    return sum5


print(findMinCost(n, m, c2, c5))
