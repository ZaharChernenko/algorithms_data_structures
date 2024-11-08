def levenstain(a, b):
    matrix = [list(range(len(b) + 1)) if i == 0 else [i] + [0] * len(b) for i in range(len(a) + 1)]
    for i in range(1, len(a) + 1):
        for j in range(1, len(b) + 1):
            if a[i - 1] == b[j - 1]:
                matrix[i][j] = matrix[i - 1][j - 1]
            else:
                matrix[i][j] = 1 + min(matrix[i - 1][j - 1], matrix[i - 1][j], matrix[i][j - 1])
    return matrix[-1][-1]


def prefixFunc(s: str) -> int:
    if len(s) <= 1:
        return 0

    prefix_arr = [0] * len(s)
    for i in range(1, len(s)):
        prev_prefix = prefix_arr[i - 1]
        while prev_prefix != 0 and s[prev_prefix] != s[i]:
            prev_prefix = prefix_arr[prev_prefix - 1]

        if s[prev_prefix] == s[i]:
            prev_prefix += 1

        prefix_arr[i] = prev_prefix

    return prefix_arr[-1]
