def levenstain(a, b):
    matrix = [[j for j in range(len(b) + 1)] if i == 0 else [i] + [0] * len(b) for i in range(len(a) + 1)]
    for i in range(1, len(a) + 1):
        for j in range(1, len(b) + 1):
            if a[i - 1] == b[j - 1]:
                matrix[i][j] = matrix[i - 1][j - 1]
            else:
                matrix[i][j] = 1 + min(matrix[i - 1][j - 1], matrix[i - 1][j], matrix[i][j - 1])
    return matrix[-1][-1]


def pifunction(a: str):
    if len(a)<=1:
        return 0
    arr = [0 for i in range(len(a))]
    for i in range(1, len(a)):
        p = arr[i-1]
        while p > 0 and a[i] != a[p]:
            p = arr[p-1]
        if a[i] == a[p]:
            p += 1
        arr[i] = p
    return arr[-1]

print(pifunction("abazxcaba" ))