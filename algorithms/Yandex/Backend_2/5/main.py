n = int(input())
arr = []
for i in range(n):
    _ = input()
    arr.append(list(map(int, input().split())))

arr.sort()

temp = arr[0][0]
s = index = start = 0
end = n
common = 0

while index < len(arr) - 1:
    for i in range(index + 1, min(end, n)):
        for l in range(common, min(len(arr[index]), len(arr[i]))):
            if arr[index][l] == arr[i][l]:
                common += 1
            else:
                break
        s += common
        if arr[index][0] != arr[i][0]:
            end = i
            break
    index += 1
    if arr[index][0] != arr[index - 1][0]:
        end = n

print(s)