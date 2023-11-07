def levenstain(a, b):
    matrix = [[j for j in range(len(b) + 1)] if i == 0 else [i] + [0] * len(b) for i in range(len(a) + 1)]
    for i in range(1, len(a) + 1):
        for j in range(1, len(b) + 1):
            if a[i - 1] == b[j - 1]:
                matrix[i][j] = matrix[i - 1][j - 1]
            else:
                matrix[i][j] = 1 + min(matrix[i - 1][j - 1], matrix[i - 1][j], matrix[i][j - 1])
    return matrix[-1][-1]


def piFunc(a: str):
    if len(a) <= 1:
        return 0
    pi_funcs_arr = [0] * len(a)
    for i in range(1, len(a)):
        prev_pi_f = pi_funcs_arr[i - 1]
        while prev_pi_f > 0 and a[i] != a[prev_pi_f]:
            prev_pi_f = pi_funcs_arr[prev_pi_f - 1]
        if a[i] == a[prev_pi_f]:
            prev_pi_f += 1
        pi_funcs_arr[i] = prev_pi_f
    return max(pi_funcs_arr)


print(piFunc("abcdabcabcdabcdab"))
