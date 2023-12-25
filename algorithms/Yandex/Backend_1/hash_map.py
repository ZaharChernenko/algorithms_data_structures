n = int(input())
d = {}
deep_dict = {}


def findDeep(index, deep: int = 1):
    global d
    global deep_dict
    if d[index] == 0:
        return deep
    elif d[index] in deep_dict:
        return deep + deep_dict[d[index]]
    return findDeep(d[index], deep + 1)


for i in range(1, n + 1):
    d[i] = int(input())
    deep_dict[i] = findDeep(i)

m = 0
deepest_index = 0
for key in deep_dict:
    if deep_dict[key] > m:
        m = deep_dict[key]
        deepest_index = key

print(deepest_index)
