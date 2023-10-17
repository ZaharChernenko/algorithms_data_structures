def convert(s: str, r: int) -> str:
    i = count = 0
    matrix = []
    full = True
    while i < len(s):
        if full:
            matrix.append([None] * r)
            for j in range(r):
                if i >= len(s):
                    break
                matrix[-1][j] = s[i]
                i += 1
            full = False
        else:
            for j in range(r - 2, 0, -1):
                matrix.append([None] * r)
                matrix[-1][j] = s[i]
                i += 1
            full = True


    res = ""
    for k in range(r):
        for j in range(len(matrix)):
            if matrix[j][k]:
                res += matrix[j][k]
    return res


print(convert("PAYPALISHIRING", 4))