def backpack(l: list, capacity):
    matrix = [[0] * capacity for i in range(len(l) + 1)]
    for i in range(1, len(l) + 1):
        for j in range(len(matrix[0])):
            if l[i - 1][1] - 1 > j:
                matrix[i][j] = matrix[i - 1][j]
            elif l[i - 1][1] - 1 == j:
                matrix[i][j] = max(l[i - 1][0], matrix[i - 1][j])
            else:
                matrix[i][j] = max(matrix[i - 1][j], matrix[i - 1][j - l[i - 1][1]] + l[i - 1][0])
    return matrix[-1][-1]


print(backpack([(1000, 1), (2000, 2), (1500, 1), (2000, 2), (5000, 8)], 9))
