def gcd(a: int, b: int):
    return a if b == 0 else gcd(b, a % b)


a, b, c, d = map(int, input().split())
m = a * d + c * b
n = b * d

d = gcd(m, n)
print(int(m / d), int(n / d))
