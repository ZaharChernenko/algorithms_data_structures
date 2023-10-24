def lengthOfLongestSubstring(s: str) -> int:
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


def removeExtraSpaces(char_list: list[str]) -> list[str]:
    count = 0
    index = 0
    while index < len(char_list):
        char_list[index - count] = char_list[index]
        index += 1
        if char_list[index - 1] == " ":
            while index < len(char_list) and char_list[index] == " ":
                index += 1
                count += 1
    for i in range(count):
        char_list.pop()
    return char_list


print(removeExtraSpaces(["a", " ", " ", "a", " ", " ", "b", " ", " "]))
