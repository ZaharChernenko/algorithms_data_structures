def z_func(s):
  z = [0] * len(s)
  left, right = 0, 0
  for i in range(1, len(s)):
    z[i] = max(0, min(z[i - left], right - i))
    while i + z[i] < len(s) and s[z[i]] == s[i + z[i]]:
      z[i] += 1
    if i + z[i] > right:
      left, right = i, i + z[i]
  return z


print(*z_func(input()))