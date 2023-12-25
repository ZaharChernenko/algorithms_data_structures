def radixSort(arr):
    n = len(str(arr[0]))
    buckets = [[] for _ in range(10)]

    for i in range(n):
        pos = n - i - 1
        for elem in arr:
            digit = int(elem[pos])
            buckets[digit].append(elem)

        print(f"Phase {i + 1}")
        for j in range(10):
            if not buckets[j]:
                print(f"Bucket {j}: empty")
                continue
            print(f"Bucket {j}:", ", ".join(buckets[j]))
        print("**********")

        index = 0
        for bucket in buckets:
            for elem in bucket:
                arr[index] = elem
                index += 1
        buckets = [[] for _ in range(10)]


size = int(input())
vec = []
for _ in range(size):
    vec.append(input())
print("Initial array:")
for i in range(size - 1):
    print(f"{vec[i]}, ", end="")
print(vec[size - 1])
print("**********")

radixSort(vec)

print("Sorted array:")
for i in range(size - 1):
    print(f"{vec[i]}, ", end="")
print(vec[size - 1])