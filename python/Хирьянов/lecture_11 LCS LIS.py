def findWaysNum(n: int, m: int) -> int:
    ways_matrix = [[1] * m if i == 0 else [1] + [0] * (m - 1) for i in range(n)]
    for i in range(1, n):
        for j in range(1, n):
            ways_matrix[i][j] = ways_matrix[i - 1][j] + ways_matrix[i][j - 1]
    return ways_matrix[-1][-1]


def matrixLCS(a, b):
    """Этот алгоритм позволяет восстановить исходную последовательность, если же нужно лишь длина, то лучше
    использовать lenLCS"""
    lcs_matrix = [[0] * (len(b) + 1) for i in range(len(a) + 1)]
    for i in range(1, len(a) + 1):
        for j in range(1, len(b) + 1):
            if a[i - 1] == b[j - 1]:
                lcs_matrix[i][j] = 1 + lcs_matrix[i - 1][j - 1]
            else:
                lcs_matrix[i][j] = max(lcs_matrix[i - 1][j], lcs_matrix[i][j - 1])
    return lcs_matrix


def lcs(a, b):
    lcs_matrix = matrixLCS(a, b)
    vert = len(a)
    hor = len(b)
    res = []
    while vert > 0 and hor > 0:
        if a[vert - 1] == b[hor - 1]:
            res.append(a[vert - 1])
            vert -= 1
            hor -= 1
        elif lcs_matrix[vert - 1][hor] > lcs_matrix[vert][hor - 1]:
            vert -= 1
        else:
            hor -= 1
    return res[::-1]


def lengthLCS(a, b) -> int:
    prev_row, current_row = [0] * (len(b) + 1), [0] * (len(b) + 1)
    for i in range(1, len(a) + 1):
        for j in range(1, len(b) + 1):
            if a[i - 1] == b[j - 1]:
                current_row[j] = 1 + prev_row[j - 1]
            else:
                current_row[j] = max(current_row[j - 1], prev_row[j])
        prev_row, current_row = current_row, [0] * (len(b) + 1)
    return prev_row[-1]


def lis(seq) -> int:
    lis_arr = [0] * len(seq) # этот массив будет хранить длину подпоследовательностей, которые
    # заканчиваются этим индексом
    for i in range(len(seq)):
        for j in range(i):
            if seq[i] > seq[j] and lis_arr[i] < lis_arr[j]:
                lis_arr[i] = lis_arr[j]
        lis_arr[i] += 1
    return max(lis_arr)


print(lis([1, 2, 3, 4, 3, 3, 2, 1, 2, 3]))