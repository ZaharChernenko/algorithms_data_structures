def middleLev(arr: list) -> list:
    lev_arr = [0] * len(arr)
    left_s, right_s = 0, sum(arr)
    lev_arr[0] = right_s - arr[0] * (len(arr))
    right_s -= arr[0]
    for i in range(1, len(arr)):
        left_s += i * (arr[i] - arr[i - 1])  # все предыдущие элементы меньше по модулю
        lev_arr[i] = left_s + right_s - arr[i] * (len(arr) - i)  # вычитаем из всех, включая текущий
        right_s -= arr[i]
    return lev_arr

input()
print(*middleLev(list(map(int, input().split()))))
