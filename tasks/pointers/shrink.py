"""
10 3
3 3 2 90 2 1 45 2 2 3 3 1 3 3 1
"""
def shrink(count_sum):
    global m, col, d, vec, left, right, min_sum
    save_left = left
    for i in range(save_left, right):
        if vec[i] <= m:
            if d[vec[i]] == 1:
                break
            d[vec[i]] -= 1
        left += 1
        count_sum -= vec[i]
    min_sum = min(min_sum, count_sum)
    d[vec[left]] -= 1
    count_sum -= vec[left]
    col.add(vec[left])
    left += 1
    while vec[left] > m: # left < right and # убрать тут
        count_sum -= vec[left]
        left += 1
    return count_sum


def run():
    global m, col, min_sum, d, vec, left, right
    count_sum = 0
    for i in range(len(vec)):
        if vec[i] <= m:
            if len(col) == m:
                left = i
            d[vec[i]] = d.setdefault(vec[i], 0) + 1
            col.discard(vec[i])

        if len(col) < m:
            count_sum += vec[i]
            if len(col) == 0:
                right = i
                count_sum = shrink(count_sum)


if __name__ == "__main__":
    n, m = map(int, input().split())
    vec = list(map(int, input().split()))
    col = {i for i in range(1, m + 1)}
    d = {}
    left = right = 0
    min_sum = float("inf")
    run()
    print(min_sum)
