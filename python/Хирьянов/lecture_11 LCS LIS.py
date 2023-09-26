def findWaysNum(n: int, m: int) -> int:
    matrix = [[1] * m if i == 0 else [1] + [0] * (m - 1) for i in range(n)]
    for i in range(1, n):
        for j in range(1, n):
            matrix[i][j] = matrix[i - 1][j] + matrix[i][j - 1]
    return matrix[-1][-1]


def matrixLCS(a, b):
    matrix = [[0] * (len(b) + 1) for i in range(len(a) + 1)]
    for i in range(1, len(a) + 1):
        for j in range(1, len(b) + 1):
            if a[i - 1] == b[j - 1]:
                matrix[i][j] = 1 + matrix[i - 1][j - 1]
            else:
                matrix[i][j] = max(matrix[i - 1][j], matrix[i][j - 1])
    return matrix


def lcs(a, b):
    matrix = matrixLCS(a, b)
    vert = len(a)
    hor = len(b)
    res = []
    while vert > 0 and hor > 0:
        if a[vert - 1] == b[hor - 1]:
            res.append(a[vert - 1])
            vert -= 1
            hor -= 1
        elif matrix[vert - 1][hor] > matrix[vert][hor - 1]:
            vert -= 1
        else:
            hor -= 1
    return res[::-1]


def lis(seq) -> int:
    arr_length_subseq = [0] * len(seq) # этот массив будет хранить длину подпоследовательностей, которые
    # заканчиваются этим индексом
    for i in range(len(seq)):
        for j in range(i):
            if seq[i] > seq[j] and arr_length_subseq[i] < arr_length_subseq[j]:
                arr_length_subseq[i] = arr_length_subseq[j]
        arr_length_subseq[i] += 1
    return max(arr_length_subseq)


print(lis([1, 2, 3, 4, 3, 3, 2, 1, 2, 3]))