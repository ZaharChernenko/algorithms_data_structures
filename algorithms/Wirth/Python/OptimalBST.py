class OptimalBST:
    def __init__(self, elements, key_freq):
        self.elements = elements
        self.n = len(elements)

        # prefix_weight[i] - суммарный вес от нулевого элемента до i НЕ включительно
        prefix_weights = [0] + key_freq
        for i in range(1, len(prefix_weights)):
            prefix_weights[i] = prefix_weights[i - 1] + prefix_weights[i]

        # self.total_cost[i][j] - взвешенный путь дерева с [i, j) элементами
        self.total_cost = [[0] * (self.n + 1) for _ in range(self.n + 1)]
        # номер вершины, начиная с 1
        self.root_number: list[list[int]] = [[-1] * (self.n + 1) for _ in range(self.n + 1)]
        # деревья высотой 1 (у них корень это элемент, а листья - фиктивные вершины)
        for i in range(self.n):
            j = i + 1
            self.total_cost[i][j] = key_freq[i]
            self.root_number[i][j] = i

        for h in range(2, self.n + 1):
            for i in range(self.n + 1 - h):
                # элементы [i, j)
                j = i + h
                root_index: int = self.root_number[i][j - 1]
                min_cost: int = self.total_cost[i][root_index] + self.total_cost[root_index + 1][j]
                weight = prefix_weights[j] - prefix_weights[i]
                for k in range(root_index + 1, self.root_number[i + 1][j] + 1):
                    new_cost = self.total_cost[i][k] + self.total_cost[k + 1][j]
                    if new_cost < min_cost:
                        min_cost = new_cost
                        root_index = k
                self.total_cost[i][j] = min_cost + weight
                self.root_number[i][j] = root_index

    def _printTree(self, i: int, j: int, level: int):
        if i < j:
            self._printTree(i, self.root_number[i][j], level + 1)
            for _ in range(level):
                print("\t", end="")
            print(self.elements[self.root_number[i][j]])
            self._printTree(self.root_number[i][j] + 1, j, level + 1)

    def printTree(self):
        self._printTree(0, self.n, 0)


bst: OptimalBST = OptimalBST(["Albert", "Ernest", "Peter"], [1, 2, 5])
bst.printTree()
# print(bst.total_cost)

# bst: OptimalBST = OptimalBST(["Albert", "Ernest", "Peter"], [1, 2, 5], [0, 0, 0, 0])
# bst.printTree()


bst: OptimalBST = OptimalBST([10, 20, 30, 40], [4, 2, 6, 3])
bst.printTree()
