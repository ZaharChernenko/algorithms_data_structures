import heapq
from typing import NamedTuple


class Vertex(NamedTuple):
    distance: int | float
    vertex: int


def dijkstra(graph: list[list[int | float]], start_vertex: int, end_vertex: int) -> int | float:
    vertexes: list[Vertex] = [Vertex(0, start_vertex - 1)]
    distances: list[int | float] = [float("inf")] * len(graph)
    distances[start_vertex - 1] = 0

    while vertexes:
        cur_vertex = heapq.heappop(vertexes)

        if cur_vertex.distance > distances[cur_vertex.vertex]:
            continue

        for neig, weight in enumerate(graph[cur_vertex.vertex]):
            new_distance: int | float = cur_vertex.distance + weight

            if new_distance < distances[neig]:
                distances[neig] = new_distance
                heapq.heappush(vertexes, Vertex(new_distance, neig))

    return distances[end_vertex - 1]
