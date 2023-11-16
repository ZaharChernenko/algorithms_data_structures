from math import ceil
def toF(num):
    arr = []
    if num % 1 == 0:
        return (num, 1)
    for i in range(1, 101):
        p = ceil(num * i)
        if abs(p - num * i) < 0.01 * i:
            if p != i:
                arr.append([p, i])
    arr.sort(key=lambda x: x[1])
    return arr[0]

n = int(input())
for i in range(n):
    num = float(input())
    print(*toF(num))