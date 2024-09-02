from bisect import bisect_left


def findWaysNum(n: int, m: int) -> int:
    ways_matrix = [[1] * m if i == 0 else [1] + [0] * (m - 1) for i in range(n)]
    for i in range(1, n):
        for j in range(1, n):
            ways_matrix[i][j] = ways_matrix[i - 1][j] + ways_matrix[i][j - 1]
    return ways_matrix[-1][-1]


def matrixLCS(seq1, seq2) -> list[list[int]]:
    matrix = [[0] * (len(seq2) + 1) for _ in range(len(seq1) + 1)]

    for i in range(1, len(seq1) + 1):
        for j in range(1, len(seq2) + 1):
            if seq1[i - 1] == seq2[j - 1]:
                matrix[i][j] = matrix[i - 1][j - 1] + 1
            else:
                matrix[i][j] = max(matrix[i - 1][j], matrix[i][j - 1])
    return matrix


def findLCS(seq1, seq2):
    """
    >>> findLCS("abccda", "acdda")
    ['a', 'c', 'd', 'a']
    """
    matrix = matrixLCS(seq1, seq2)
    vert, hor = len(seq1), len(seq2)
    res = []

    while vert * hor > 0:
        if seq1[vert - 1] == seq2[hor - 1]:
            res.append(seq1[vert - 1])
            vert -= 1
            hor -= 1
        elif matrix[vert - 1][hor] > matrix[vert][hor - 1]:
            vert -= 1
        else:
            hor -= 1
    return res[::-1]


def lengthLCS(seq1, seq2) -> int:
    """
    >>> lengthLCS("abcd", "abc")
    3
    """
    prev_row, cur_row = [0] * (len(seq1) + 1), [0] * (len(seq2) + 1)
    for i in range(len(seq1)):
        for j in range(1, len(seq2) + 1):
            if seq1[i] == seq2[j - 1]:
                cur_row[j] = prev_row[j - 1] + 1
            else:
                cur_row[j] = max(prev_row[j], cur_row[j - 1])
        prev_row, cur_row = cur_row, [0] * (len(seq2) + 1)
    return prev_row[-1]


def lisSquare(seq) -> int:
    """this function finds largest increasing subsequence"""
    lis_arr = [0] * len(seq)

    for i in range(len(seq)):
        for j in range(i):
            if seq[i] > seq[j] and lis_arr[i] < lis_arr[j]:
                lis_arr[i] = lis_arr[j]
        lis_arr[i] += 1
    return max(lis_arr)


def lenLIS(seq) -> int:
    """
    >>> lenLIS([4, 5, 6, 1, 2, 3, 4])
    4
    """
    min_num = [float("inf")] * (len(seq) + 1)
    min_num[0] = float("-inf")
    length = 0
    for i in range(len(seq)):
        ge_index = bisect_left(min_num, seq[i])
        if min_num[ge_index - 1] < seq[i] < min_num[ge_index]:
            min_num[ge_index] = seq[i]
            length = max(length, ge_index)
    return length


def LIS[T](sequence: list[T]) -> list[T]:
    lis_arr: list[int | float] = [float("inf")] * (len(sequence) + 1)
    lis_arr[0] = float("-inf")
    prev_arr: list[int | float] = [float("-inf")] * len(sequence)
    length: int = 0

    for i in range(len(sequence)):
        # значение, которое вернет key, будет сравниваться с val
        ge_index: int = bisect_left(
            lis_arr, sequence[i], key=lambda index: index if abs(index) == float("inf") else sequence[index]
        )
        if lis_arr[ge_index] == float("inf") or sequence[i] < sequence[lis_arr[ge_index]]:
            lis_arr[ge_index] = i
            prev_arr[i] = lis_arr[ge_index - 1]
            length = max(length, ge_index)

    result: list[T | None] = [None] * length
    seq_index: int = lis_arr[length]
    for index in range(length - 1, -1, -1):
        result[index] = sequence[seq_index]
        seq_index = prev_arr[seq_index]

    return result


if __name__ == "__main__":
    import doctest

    doctest.testmod()
    print(LIS([1, 3, 6, 7, 9, 4, 10, 5, 6]))
