def validExp(exp):
    tokens = {"(": ")", "[": "]", "{": "}"}
    stack = []
    for elem in exp:
        if elem in tokens:
            stack.append(elem)
        elif elem in ")]}":
            if not stack or tokens[stack.pop()] != elem:
                return "no"
    return "yes" if len(stack) == 0 else "no"

print(validExp(input()))
