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
