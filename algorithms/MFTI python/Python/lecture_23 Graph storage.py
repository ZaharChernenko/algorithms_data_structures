from collections import defaultdict

# adjacency matrix
# if vertexes aren't numbers

N_VERTEXES, N_EDGES = map(int, input().split())


def createAdjMatrix(N_VERTEXES: int, N_EDGES: int):
    from_index2name_arr: list[str | None] = [None] * N_VERTEXES
    from_name2index_dict: dict[str, int] = {}

    adj_matrix: list[list[bool]] = [[False] * N_VERTEXES for _ in range(N_VERTEXES)]
    cur_ver_index = 0

    for _ in range(N_EDGES):
        vertexes = input().split()
        for v1, v2 in vertexes, reversed(vertexes):
            if not v1 in from_name2index_dict:
                from_name2index_dict[v1] = cur_ver_index
                from_index2name_arr[cur_ver_index] = v1
                cur_ver_index += 1
            adj_matrix[from_name2index_dict[v1]][from_name2index_dict[v2]] = True
            adj_matrix[from_name2index_dict[v2]][from_name2index_dict[v1]] = True

    print(adj_matrix)


def createAdjList(N_EDGES):
    adj_list: dict[str, list[str]] = defaultdict(list)

    for _ in range(N_EDGES):
        v1, v2 = input().split()
        adj_list[v1].append(v2)
        adj_list[v2].append(v1)

    print(adj_list)


createAdjList(N_EDGES)
