def radixSort(arr):
    n = 6
    count = [0 for _ in range(10)]
    pos = [0 for _ in range(10)]
    new_arr = [0 for _ in range(len(arr))]

    for i in range(n):
        for elem in arr:
            digit = elem // 10 ** i % 10
            count[digit] += 1

        for j in range(1, 10):
            pos[j] = pos[j - 1] + count[j - 1]

        for elem in arr:
            digit = elem // 10 ** i % 10
            new_arr[pos[digit]] = elem
            pos[digit] += 1; count[digit] -= 1
        pos[0] = 0
        for j in range(len(new_arr)):
            arr[j] = new_arr[j]


size = int(input())
vec = []
for _ in range(size):
    vec.append(int(input()))
radixSort(vec)
print(vec)