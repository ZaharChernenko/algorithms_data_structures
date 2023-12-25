def merge(res_arr:list, left_arr: list, right_arr: list) -> list:
    index = left_index = right_index = 0
    while left_index < len(left_arr) and right_index < len(right_arr):
        if left_arr[left_index] <= right_arr[right_index]:
            res_arr[index] = left_arr[left_index]
            left_index += 1
        else:
            res_arr[index] = right_arr[right_index]
            right_index += 1
        index += 1
    for i in range(left_index, len(left_arr)):
        res_arr[index] = left_arr[i]
        index += 1
    for i in range(right_index, len(right_arr)):
        res_arr[index] = right_arr[i]
        index += 1
    return res_arr


def mergeSort(arr: list) -> list:
    if len(arr) <= 1: return arr
    return merge(arr, mergeSort(arr[:len(arr) // 2]), mergeSort(arr[len(arr) // 2:]))

input()
user_arr = list(map(int, input().split()))
print(*mergeSort(user_arr))
