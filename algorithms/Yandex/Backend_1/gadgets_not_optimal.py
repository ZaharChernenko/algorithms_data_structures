"""Вася подсчитал, что у него есть m гаджетов, которые нужно подключить к USB и всего n USB-портов на компьютере.
В ближайшем интернет-магазине продаются разветвители с одного USB на два за c2 рублей и
USB-хабы с одного USB на 5 по c5 рублей.
Разветвители и хабы можно подключать друг к другу и к USB-портам компьютера.
Определите, какое минимальное количество рублей нужно потратить Васе, чтобы подключить все USB устройства.
При этом можно обеспечить возможность подключить и больше
m гаджетов, главное минимизировать цену."""
import math

ports_num = int(input())
gadgets_num = int(input())
cost2 = int(input())
cost5 = int(input())

if ports_num >= gadgets_num:
    print(0)

else:
    if cost5 <= cost2:
        print(math.ceil((gadgets_num - ports_num) / 4) * cost5)
    else:
        diff = gadgets_num - ports_num
        cost_arr = [0] * 5
        start = 4
        while diff > 0:
            cost_arr[start] = min(cost_arr[(start - 1) % 5] + cost2, cost_arr[(start - 4) % 5] + cost5)
            start = (start + 1) % 5
            diff -= 1
        print(cost_arr[(start - 1) % 5])