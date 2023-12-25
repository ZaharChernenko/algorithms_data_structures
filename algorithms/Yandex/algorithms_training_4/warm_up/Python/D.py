def check(first: str, second: str) -> str:
    freq_d = {}
    for elem in first:
        freq_d[elem] = freq_d.setdefault(elem, 0) + 1
    for elem in second:
        if elem not in freq_d:
            return "NO"
        freq_d[elem] -= 1
        if freq_d[elem] == 0:
            del freq_d[elem]
    return "NO" if freq_d else "YES"


print(check(input(), input()))