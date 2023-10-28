def zabor():
    n, k = map(int, input().split())
    arr = list(map(int, input().split()))
    arr.sort()
    min_diff = float('inf')

    left = 0
    right = n - k - 1 #здесь нужен именно указатель на индекс, срез не используется, поэтому нужно вычесть 1

    while right < n:
        diff = arr[right] - arr[left]
        min_diff = min(min_diff, diff)

        left += 1
        right += 1