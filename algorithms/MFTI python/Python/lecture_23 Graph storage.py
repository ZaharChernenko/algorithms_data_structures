from collections import defaultdict


def createAdjMatrix(n_vertex: int, n_edges: int):
    from_index2name_arr: list[str | None] = [None] * n_vertex
    from_name2index_dict: dict[str, int] = {}
    adj_matrix: list[list[bool]] = [[False] * n_vertex for _ in range(n_vertex)]

    cur_index: int = 0
    for _ in range(n_edges):
        v1, v2 = input().split()
        for v in v1, v2:
            if v not in from_name2index_dict:
                from_name2index_dict[v] = cur_index
                from_index2name_arr[cur_index] = v
                cur_index += 1

        v1_index = from_name2index_dict[v1]
        v2_index = from_name2index_dict[v2]

        adj_matrix[v1_index][v2_index] = True
        adj_matrix[v2_index][v1_index] = True

    print(adj_matrix)


def createAdjDict(n_edges: int):
    adj_dict: dict[str, list[str]] = defaultdict(list)

    for _ in range(n_edges):
        v1, v2 = input().split()
        adj_dict[v1].append(v2)
        adj_dict[v2].append(v1)

    print(adj_dict)


N_VERTEX, N_EDGES = map(int, input().split())
createAdjDict(N_EDGES)
