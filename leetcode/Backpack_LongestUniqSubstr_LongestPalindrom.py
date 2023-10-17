def backpack(l: list):
    matrix = [[0] * max(l, key=lambda el: el[1])[1] for i in range(len(l) + 1)]
    for i in range(1, len(l) + 1):
        for j in range(len(matrix[0])):
            if l[i - 1][1] - 1 > j:
                matrix[i][j] = matrix[i - 1][j]
            elif l[i - 1][1] - 1 == j:
                matrix[i][j] = max(l[i - 1][0], matrix[i - 1][j])
            else:
                matrix[i][j] = max(matrix[i - 1][j], matrix[i - 1][j - l[i - 1][1]] + l[i - 1][0])
    return matrix[-1][-1]


print(backpack([(1000, 1), (2000, 2), (1500, 1), (2000, 2), (5000, 8)]))


# это решение почему-то быстрее чем эталонное
def lengthOfLongestSubstring1(s: str) -> int:
    m = 0
    res = ""
    for elem in s:
        i = s.find(elem)
        if i == -1:
            res += elem
        else:
            m = max(m, len(res))
            res = res[i + 1:] + elem
    m = max(m, len(res))
    return m


# эталонное вот
def lengthOfLongestSubstring2(s: str) -> int:
    left = m = 0
    uniq = set()
    for elem in s:
        if elem in uniq:
            m = max(len(uniq), m)
            while elem in uniq:
                uniq.remove(s[left])
                left += 1
        uniq.add(elem)
    m = max(len(uniq), m)
    return m


def longestPalindrome(s: str) -> str:
    if s == s[::-1]: return s

    start, size = 0, 1
    for i in range(1, len(s)):
        l, r = i - size, i + 1
        s1, s2 = s[l - 1:r], s[l:r]

        if l - 1 >= 0 and s1 == s1[::-1]:
            start, size = l - 1, size + 2
        elif s2 == s2[::-1]:
            start, size = l, size + 1

    return s[start:start + size]


print(longestPalindrome("daacaad"))
