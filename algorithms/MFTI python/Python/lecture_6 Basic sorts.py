def insertSort[T](arr: list[T]) -> list[T]:
    """Сортировка вставками"""
    temp_arr: list[T] = arr.copy()
    for top in range(1, len(temp_arr)):
        for i in range(top, 0, -1):
            if temp_arr[i - 1] <= temp_arr[i]:
                break
            temp_arr[i - 1], temp_arr[i] = temp_arr[i], temp_arr[i - 1]

    return temp_arr


def choiceSort[T](arr: list[T]) -> list[T]:
    """Сортировка выбором"""
    temp_arr: list[T] = arr.copy()
    for pos in range(len(temp_arr)):
        for i in range(pos + 1, len(temp_arr)):
            if temp_arr[i] < temp_arr[pos]:
                temp_arr[i], temp_arr[pos] = temp_arr[pos], temp_arr[i]

    return temp_arr


def bubbleSort[T](arr: list[T]) -> list[T]:
    """Сортировка пузырьком"""
    temp_arr: list[T] = arr.copy()
    for bypass in range(len(temp_arr) - 1):
        for i in range(1, len(temp_arr) - bypass):
            if temp_arr[i - 1] > temp_arr[i]:
                temp_arr[i - 1], temp_arr[i] = temp_arr[i], temp_arr[i - 1]

    return temp_arr


def bubbleSortWithSortCheck[T](arr: list[T]) -> list[T]:
    """Сортировка пузырьком с проверкой на упорядоченность"""
    temp_arr: list[T] = arr.copy()
    for bypass in range(len(temp_arr) - 1):
        is_sorted: bool = True
        for i in range(1, len(temp_arr) - bypass):
            if temp_arr[i - 1] > temp_arr[i]:
                is_sorted = False
                temp_arr[i - 1], temp_arr[i] = temp_arr[i], temp_arr[i - 1]
        if is_sorted:
            break

    return temp_arr


def countSort(arr: list[int]) -> list[int]:
    """Сортировка подсчетом"""
    pos_arr: list[int] = [0] * (max(arr) + 1)
    for elem in arr:
        pos_arr[elem] += 1

    prev_pos: int = 0
    prev_count: int = 0
    for i in range(len(pos_arr)):
        prev_pos = cur_pos = prev_pos + prev_count
        prev_count = pos_arr[i]
        pos_arr[i] = cur_pos

    temp_arr: list[int] = [0] * len(arr)
    for elem in arr:
        temp_arr[pos_arr[elem]] = elem
        pos_arr[elem] += 1

    return temp_arr


if __name__ == "__main__":
    import timeit

    def test(func: "function"):
        print(func.__doc__)
        measureSort(func, list(range(1000, 2000)) + list(range(1000)), list(range(2000)))
        measureSort(func, [3, 2, 1], [1, 2, 3])
        measureSort(func, list(range(10_000, -1, -1)), list(range(10_001)))
        print()

    def measureSort[T](func, cur_arr: list[T], correct_arr: list[T]):
        start: int = timeit.time.time_ns()
        cur_arr = func(cur_arr)
        print("time: ", timeit.time.time_ns() - start)
        assert cur_arr == correct_arr

    test(insertSort)
    test(choiceSort)
    test(bubbleSort)
    test(bubbleSortWithSortCheck)
    test(countSort)
    test(sorted)
