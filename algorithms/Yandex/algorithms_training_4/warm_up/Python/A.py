def notMin(arr: list, left:int, right:int):
    cur = arr[left]
    for i in range(left + 1, right + 1):
        if cur > arr[i]:
            return cur
        if cur < arr[i]:
            return arr[i]
    return "NOT FOUND"


arr_size, n_req = map(int, input().split())

arr = list(map(int, input().split()))

for i in range(n_req):
    print(notMin(arr, *map(int, input().split())))
