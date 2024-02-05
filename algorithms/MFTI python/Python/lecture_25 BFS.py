from collections import deque

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


def bfs(graph: list[list[int]]):
    vertexes: deque[int] = deque([0])
    distances_arr: list[int] = [-1] * len(graph)
    distances_arr[0] = 0

    while vertexes:
        cur_vertex = vertexes.popleft()
        for neig in graph[cur_vertex]:
            if distances_arr[neig] == -1:
                vertexes.append(neig)
                distances_arr[neig] = distances_arr[cur_vertex] + 1

    return distances_arr


def findShortestLen(graph: list[list[int]], start_vertex: int, end_vertex: int) -> int:
    vertexes: deque[int] = deque([start_vertex])
    distances_arr: list[int] = [-1] * len(graph)
    distances_arr[start_vertex] = 0
    is_found: bool = False

    while vertexes and not is_found:
        cur_vertex: int = vertexes.popleft()
        for neig in graph[cur_vertex]:
            if distances_arr[neig] == -1:
                vertexes.append(neig)
                distances_arr[neig] = distances_arr[cur_vertex] + 1

            if neig == end_vertex:
                is_found = True
                break

    return distances_arr[end_vertex]


def getParents(graph: list[list[int]], root: int) -> list[int]:
    vertexes: deque[int] = deque([root])
    parents_arr: list[int] = [-1] * len(graph)

    while vertexes:
        cur_vertex: int = vertexes.popleft()
        for neig in graph[cur_vertex]:
            if parents_arr[neig] == -1 and neig != root:
                vertexes.append(neig)
                parents_arr[neig] = cur_vertex

    return parents_arr


def findShortestPath(graph: list[list[int]], start_vertex: int, end_vertex: int) -> list[int]:
    vertexes: deque[int] = deque([start_vertex])
    parents: list[int] = [-1] * len(graph)

    is_found: bool = False
    while vertexes and not is_found:
        cur_vertex = vertexes.popleft()
        for neig in graph[cur_vertex]:
            if parents[neig] == -1 and neig != start_vertex:
                vertexes.append(neig)
                parents[neig] = cur_vertex

            if neig == end_vertex:
                is_found = True
                break

    cur_vertex = end_vertex
    path: list[int] = [cur_vertex]
    while (cur_vertex := parents[cur_vertex]) != -1:
        path.append(cur_vertex)
    path.reverse()

    return path


def findShortestPathDict(graph: dict[str, set[str]], start_vertex: str, end_vertex: str) -> list[str]:
    vertexes: deque[str] = deque([start_vertex])
    parents: dict[str, str | None] = {vertex: None for vertex in graph}
    is_found: bool = False

    while vertexes and not is_found:
        cur_vertex = vertexes.popleft()
        for neig in graph[cur_vertex]:
            if not parents[neig] and neig != start_vertex:
                vertexes.append(neig)
                parents[neig] = cur_vertex

            if cur_vertex == end_vertex:
                is_found = True
                break

    cur_vertex = end_vertex
    path: list[str] = [cur_vertex]
    while (cur_vertex := parents[cur_vertex]):
        path.append(cur_vertex)
    path.reverse()

    return path


def addEdge(graph: dict[str, set[str]], v1, v2):
    graph[v1].add(v2)
    graph[v2].add(v1)


def horse(start_vertex: str, end_vertex: str) -> list[str]:
    rows: str = "abcdefgh"
    cols: str = "12345678"
    graph: dict[str, set[str]] = {row + col: set() for col in cols for row in rows}

    for i in range(8):
        for j in range(8):
            v1 = rows[i] + cols[j]

            if 0 <= i + 2 < 8 and 0 <= j + 1 < 8:
                v2 = rows[i + 2] + cols[j + 1]
                addEdge(graph, v1, v2)

            if 0 <= i - 2 < 8 and 0 <= j + 1 < 8:
                v2 = rows[i - 2] + cols[j + 1]
                addEdge(graph, v1, v2)

            if 0 <= i + 1 < 8 and 0 <= j + 2 < 8:
                v2 = rows[i + 1] + cols[j + 2]
                addEdge(graph, v1, v2)

            if 0 <= i - 1 < 8 and 0 <= j + 2 < 8:
                v2 = rows[i - 1] + cols[j + 2]
                addEdge(graph, v1, v2)

    return findShortestPathDict(graph, start_vertex, end_vertex)


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

print(findShortestPath(g1, 1, 7))
print(horse("d4", "f7"))
print(bfs(g1))
