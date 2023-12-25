def prefixFunc(a: str):
    if len(a) <= 1:
        return 0
    prefix_funcs_arr = [0] * len(a)
    for i in range(1, len(a)):
        prev_prefix_val = prefix_funcs_arr[i - 1]
        while prev_prefix_val > 0 and a[i] != a[prev_prefix_val]:
            prev_prefix_val = prefix_funcs_arr[prev_prefix_val - 1]
        if a[i] == a[prev_prefix_val]:
            prev_prefix_val += 1
        prefix_funcs_arr[i] = prev_prefix_val
    return prefix_funcs_arr[-1]

string = input()
print(len(string) - prefixFunc(string))