import math
capacity = int(input())
floors = int(input())
stack = []

for i in range(1, floors + 1):
    n_people = int(input())
    if n_people > 0:
        stack.append([i, n_people])

count = 0
while stack:
    nums_to_cur_floor = math.ceil(stack[-1][1] / capacity)
    count += nums_to_cur_floor * 2 * stack[-1][0]
    cur_cap = nums_to_cur_floor * capacity - stack[-1][1]
    stack.pop()
    while stack and cur_cap > 0:
        take = min(cur_cap, stack[-1][1])
        stack[-1][1] -= take
        cur_cap -= take
        if stack[-1][1] == 0:
            stack.pop()

print(count)