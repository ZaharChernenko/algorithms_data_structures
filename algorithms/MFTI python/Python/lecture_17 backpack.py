def backpack(prices_arr: list, weights_arr: list[int], capacity: int):
    backpack_2d = [[0] * (capacity + 1) for _ in range(len(prices_arr) + 1)]

    for row in range(1, len(prices_arr) + 1):
        for cur_capacity in range(1, len(prices_arr) + 1):
            if cur_capacity < weights_arr[row - 1]:
                backpack_2d[row][cur_capacity] = backpack_2d[row - 1][cur_capacity]
            else:
                backpack_2d[row][cur_capacity] = max(
                    backpack_2d[row - 1][cur_capacity],
                    prices_arr[row - 1] + backpack_2d[row - 1][cur_capacity - weights_arr[row - 1]])
    return backpack_2d[-1][-1]


print(backpack([1000, 1500, 2000, 3000], [1, 1, 3, 4], 4))


def backpackDiscr(profit_matrix: list[list[int]], discr_step: int, total_invest: int):
    """Идея задачи заключается в том, что дан максимальный размер инвестиций, а также ее
    дискретность - другими словами шаг. Также дана матрица со значениями инвестиций, где
    aij - количество заработанных денег при инвестировании в i предприятие j * шаг денег"""
    backpack_2d: list[list[int]] = [[0] * (total_invest // discr_step + 1) for _ in range(len(profit_matrix) + 1)]

    for row_index in range(1, len(profit_matrix) + 1):
        for capacity in range(1, total_invest // discr_step + 1):
            cur_max: int = 0
            for cur_capacity in range(1, capacity + 1):
                cur_max = max(cur_max, profit_matrix[row_index - 1][cur_capacity - 1]
                              + backpack_2d[row_index - 1][capacity - cur_capacity])
            backpack_2d[row_index][capacity] = max(cur_max, backpack_2d[row_index - 1][capacity])

    return backpack_2d[-1][-1]


profit_matrix: list[list[int]] = [[11, 16, 23, 32, 38],
                                  [12, 15, 24, 31, 39],
                                  [10, 17, 22, 32, 40],
                                  [11, 14, 25, 30, 38]]
print(backpackDiscr(profit_matrix, 50, 250))


profit_matrix = [[8, 13, 22, 31, 39],
                 [10, 12, 21, 38, 40],
                 [7, 14, 22, 29, 38],
                 [10, 13, 23, 30, 41]]
print(backpackDiscr(profit_matrix, 50, 250))
