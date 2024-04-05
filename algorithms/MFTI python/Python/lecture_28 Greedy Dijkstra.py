def findMinNotUsed(distances: list[int], visisted: list[bool]) -> int:
    index: int | None = None
    for i, distance in enumerate(distances):
        if not visisted[i] and (index is None or distances[index] > distance):
            index = i

    return index


def dijkstraGreedy(graph: list[list[int]], start_vertex: int, end_vertex: int) -> int | float:
    visited: list[bool] = [False] * len(graph)
    distances: list[int | float] = [float("inf")] * len(graph)
    distances[start_vertex - 1] = 0

    while not visited[end_vertex - 1]:
        cur_vertex: int = findMinNotUsed(distances, visited)

        for neig, weight in enumerate(graph[cur_vertex]):
            new_distance: int | float = distances[cur_vertex] + weight
            distances[neig] = min(distances[neig], new_distance)

        visited[cur_vertex] = True

    return distances[end_vertex - 1] if distances[end_vertex - 1] != float("inf") else -1
