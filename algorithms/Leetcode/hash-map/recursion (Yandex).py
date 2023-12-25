"""Определим близость двух целочисленных массивов как длину их
наибольшего совпадающего префикса (см. примечание).
Примеры:
Близость [1, 2, 1, 3] и [1, 2, 3, 2] равна 2 — префикс [1, 2] совпадает;
Близость [1, 2, 3] и [3, 2, 1] равна 0.
Дано n целочисленных массивов a1, a2, …, an.
Необходимо вычислить сумму близостей массивов ai и aj для каждой пары 1 ≤ i < j ≤ n."""


"""
5
3
1 2 3
4
1 2 3 4 5
4
1 2 3 4
2
5 2
1
5
Ans: 11
"""

"""
6
3
1 2 3
4
1 2 3 4 5 3 4 5
4
1 2 3 4
2
5 2
5
3 1 2 3 4
4
4 2 1 3
Ans: 10
"""

"""
3
2
1 2
2
1 3
3
1 4 5
Ans: 3
"""


def countPrefix(_vec: list, d: dict, deep: int = 0):
    _count = 0
    if not d:
        return 0
    """Бежим по каждому ключу"""
    for key in d:
        """Делим на 2, потому что при простом умножении считается дважды"""
        _count += len(d[key]) * (len(d[key]) - 1) / 2
        new_d = {}
        max_len = 0
        for index in d[key]:
            """Если следующего элемента не существует, пропускаем вектор"""
            if len(_vec[index]) <= deep + 1:
                continue
            """Иначе добавляем в ключ новый индекс"""
            new_d[_vec[index][deep + 1]] = new_d.setdefault(_vec[index][deep + 1], [])
            new_d[_vec[index][deep + 1]].append(index)
            """Считаем максимальную длину, чтобы уменьшить количество рекурсивных вызовов"""
            max_len = max(max_len, len(new_d[_vec[index][deep + 1]]))

        """Если максимальная длина меньше 1, то вектор всего лишь один, то близость равна 0,
        можно просто не прибавлять ничего"""
        if max_len > 1:
            _count += countPrefix(_vec, new_d, deep + 1)

    return int(_count)


size_vec = int(input())
vec = []
zero_elem_dict = {}

for i in range(size_vec):
    _ = input()
    vec.append(list(map(int, input().split())))
    """Создаем начальный словарь, который будет содержать как ключ, все возможные значения нулевого
    индекса, а значением будет список индексов, вектора"""
    zero_elem_dict[vec[i][0]] = zero_elem_dict.setdefault(vec[i][0], [])
    zero_elem_dict[vec[i][0]].append(i)

print(countPrefix(vec, zero_elem_dict))
