""" Дано первые четыре цифры телефонного номера,
    выяснить, сколько максимально возможных последовательностей из
    возрастающих на 1, убывающих на 1, равных предыдущему
"""

def findMax(a):
    incr = decr= equal = 1
    for i in range(3):
        if int(a[i]) + 1 == int(a[i + 1]):
            incr += 1
            decr = 1
            equal = 1
        elif int(a[i]) - 1 == int(a[i + 1]):
            incr = 1
            decr += 1
            equal = 1
        elif int(a[i]) == int(a[i + 1]):
            incr = 1
            decr = 1
            equal += 1
        else:
            incr = decr = equal = 1

    incr += min(7, 9 - int(a[3]))
    decr+= min(7, int(a[3]))
    equal += 7
    arr = [incr, decr, equal]
    return arr.count(max(arr))


response = input()
print(findMax(response))

