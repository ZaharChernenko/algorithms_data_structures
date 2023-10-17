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


#
def lengthOfLongestSubstring(s: str) -> int:
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


def longestPalindrome(s: str) -> str:
    for i in range(len(s), 0, -1):
        if i % 2 == 0:
            print(s[i:i // 2 - 1:-1])
            if s[:i // 2] == s[i:i // 2 - 1:-1]:
                return s[:i]
        else:
            if s[:i // 2] == s[i:i // 2:-1]:
                return s[:i]


longestPalindrome("cbbd")
