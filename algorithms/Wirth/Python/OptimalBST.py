# https://www.geeksforgeeks.org/problems/optimal-binary-search-tree2214/1
# https://www.javatpoint.com/optimal-binary-search-tree


class OptimalBST[T]:
    def __init__(self, elements: list[T], key_freq: list[int]):
        # elements должны быть упорядочены
        self.elements: list[T] = elements
        self.n: int = len(elements)

        # prefix_weight[i] - суммарный вес от нулевого элемента до i НЕ включительно
        prefix_weights: list[int] = [0] + key_freq
        for i in range(1, len(prefix_weights)):
            prefix_weights[i] = prefix_weights[i - 1] + prefix_weights[i]

        # self.total_cost[i][j] - взвешенный путь дерева с [i, j) элементами
        self.total_cost: list[list[int]] = [[0] * (self.n + 1) for _ in range(self.n + 1)]
        # номера корней оптимальных деревьев [i, j)
        self.root_index: list[list[int]] = [[-1] * (self.n + 1) for _ in range(self.n + 1)]
        # инициализация оптимальных деревьев высоты 1, по сути имеем только вес вершины
        for i in range(self.n):
            j = i + 1
            self.total_cost[i][j] = key_freq[i]
            self.root_index[i][j] = i

        # инициализация оптимальных деревьев от двух элементов до всех
        for h in range(2, self.n + 1):
            for i in range(self.n + 1 - h):
                # элементы [i, j) входят в дерево
                j = i + h
                # берем предыдущую оптимальную вершину
                root_index: int = self.root_index[i][j - 1]
                # берем поддеревья предыдущего оптимального дерева
                min_cost: int = self.total_cost[i][root_index] + self.total_cost[root_index + 1][j]
                # находим вес всех вершин [i, j)
                weight: int = prefix_weights[j] - prefix_weights[i]
                # перебор всех остальных вершин в качестве нового корня
                for new_root_index in range(root_index + 1, self.root_index[i + 1][j] + 1):
                    new_cost = self.total_cost[i][new_root_index] + self.total_cost[new_root_index + 1][j]
                    if new_cost < min_cost:
                        min_cost = new_cost
                        root_index = new_root_index
                # к взевешенному пути прибавляем вес всех вершин, т.к. все они будут на уровень выше в новом дереве
                self.total_cost[i][j] = min_cost + weight
                self.root_index[i][j] = root_index

    def _printTree(self, i: int, j: int, level: int):
        if i < j:
            self._printTree(i, self.root_index[i][j], level + 1)
            for _ in range(level):
                print("\t", end="")
            print(self.elements[self.root_index[i][j]])
            self._printTree(self.root_index[i][j] + 1, j, level + 1)

    def printTree(self):
        # печатаем оптимальное дерево [i, j)
        self._printTree(0, self.n, 0)


class OptimalBSTWithMisses[T](OptimalBST):
    def __init__(self, elements: list[T], key_freq: list[int], misses_freq: list[int]):
        self.elements: list[T] = elements
        self.n: int = len(elements)

        # prefix_weight[i] - суммарный вес от нулевого элемента до i НЕ включительно, однако
        # с весом фиктивной вершины, i - 1 < vertex < i
        # prefix_weight[0] - количество запросов на поиск элемента, меньше самого маленькой из elements
        # допустим это universum .  .  .  .  .
        #                       / \/ \/ \/ \/ \
        # prefix_weight[1]  .
        #                  / \
        # это prefix_weight[2]  .  .
        #                      / \/ \
        prefix_weights: list[int] = [misses_freq[0]] + key_freq
        for i in range(1, len(prefix_weights)):
            prefix_weights[i] += prefix_weights[i - 1] + misses_freq[i]
        # self.total_cost[i][j] - взвешенный путь дерева с [i, j) элементами
        self.total_cost: list[list[int]] = [[0] * (self.n + 1) for _ in range(self.n + 1)]
        # номера корней оптимальных деревьев [i, j)
        self.root_index: list[list[int]] = [[-1] * (self.n + 1) for _ in range(self.n + 1)]
        # инициализация оптимальных деревьев высоты 1, по сути имеем только вес вершины
        for i in range(self.n):
            j = i + 1
            # здесь вычитается вес самой правой фиктивной вершины у i, который мы обратно прибавляем,
            # т.к. она является самой левой фиктивной вершиной у j
            self.total_cost[i][j] = prefix_weights[j] - prefix_weights[i] + misses_freq[i]
            self.root_index[i][j] = i

        # инициализация оптимальных деревьев от двух элементов до всех
        for h in range(2, self.n + 1):
            for i in range(self.n + 1 - h):
                # элементы [i, j) входят в дерево
                j = i + h
                # берем предыдущую оптимальную вершину
                root_index: int = self.root_index[i][j - 1]
                # берем поддеревья предыдущего оптимального дерева
                min_cost: int = self.total_cost[i][root_index] + self.total_cost[root_index + 1][j]
                # находим вес всех вершин [i, j)
                # если 0, то нам нужно не забыть добавить самый левый элемент
                weight: int = prefix_weights[j] if i == 0 else prefix_weights[j] - prefix_weights[i] + misses_freq[i]
                # перебор всех остальных вершин в качестве нового корня
                for new_root_index in range(root_index + 1, self.root_index[i + 1][j] + 1):
                    new_cost = self.total_cost[i][new_root_index] + self.total_cost[new_root_index + 1][j]
                    if new_cost < min_cost:
                        min_cost = new_cost
                        root_index = new_root_index
                # к взевешенному пути прибавляем вес всех вершин, т.к. все они будут на уровень выше в новом дереве
                self.total_cost[i][j] = min_cost + weight
                self.root_index[i][j] = root_index


print("Оптимальное дерево без веса промахов")
bst: OptimalBST = OptimalBST(["Albert", "Ernest", "Peter"], [1, 2, 5])
bst.printTree()

print("Оптимальное дерево с весом промахов")
bst = OptimalBSTWithMisses(["Albert", "Ernest", "Peter"], [1, 2, 5], [20, 10, 1, 1])
bst.printTree()

print("Оптимальное дерево без веса промахов")
bst = OptimalBST([10, 20, 30, 40], [4, 2, 6, 3])
bst.printTree()
