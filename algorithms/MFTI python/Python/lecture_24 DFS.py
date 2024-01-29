def dfs(now: int, graph: list[list[int]], visited: list[bool]):
    visited[now] = True
    for neig in graph[now]:
        if not visited[neig]:
            dfs(neig, graph, visited)


def countComp(graph):
    visited = [False] * len(graph)
    comp = 0
    for vertex in range(len(graph)):
        if not visited[vertex]:
            dfs(vertex, graph, visited)
            comp += 1
    return comp


g = [
    [1],
    [2],
    [0, 3],
    [4],
    [3]
]


g1 = [
    [1],
    [2, 6],
    [0, 6],
    [5],
    [3, 7],
    [4, 7],
    [7],
    [6]
]


def _dfsKosaraju(now: int, graph: list[list[int]], visited: list[bool], stack: list[int]):
    visited[now] = True
    for neig in graph[now]:
        if not visited[neig]:
            _dfsKosaraju(neig, graph, visited, stack)
    stack.append(now)


def getStack(graph: list[list[int]]) -> list[int]:
    visited = [False] * len(graph)
    stack: list[int] = []
    for vertex in range(len(graph)):
        if not visited[vertex]:
            _dfsKosaraju(vertex, graph, visited, stack)
    return stack


def invertGraph(graph: list[list[int]]) -> list[list[int]]:
    inverted_graph: list[list[int]] = [[] for _ in range(len(graph))]

    for row_index, row in enumerate(graph):
        for vertex in row:
            inverted_graph[vertex].append(row_index)

    return inverted_graph


def kosaraju(graph: list[list[int]]) -> int:
    stack = getStack(graph)[::-1]
    inverted_graph = invertGraph(graph)
    visited: list[bool] = [False] * len(graph)
    comp = 0

    for vertex in stack:
        if not visited[vertex]:
            dfs(vertex, inverted_graph, visited)
            comp += 1

    return comp


print(invertGraph(g1))
print(kosaraju(g))
print(kosaraju(g1))
