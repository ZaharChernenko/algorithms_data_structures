""" начнем со сравнения полиномов - многочлен типа
    С0 + С1 * X ^ 1 + C2 * X ^ 2 + ... + Cn * X ^ n
"""

""" Идея заключается в том, чтобы взять конкретный X
    и подставить его в оба полинома, тогда если
    значения разные, то мы можем утверждать, что
    и полиномы тоже разные, с другой стороны, если
    значения совпадают, то возможно и полиномы тоже
    совпадают, чтобы это узнать наверняка необходимо
    взять Х n + 1 раз, иначе есть шанс коллизии
"""

""" Допустим у нас есть массивы, в которых хранятся
    значения коэффициентов каждого члена, размером
    n + 1, т.к мы начинаем с 0 и до n
"""
x = 1
a = [1, 2, 1]
res = 0
for i in range(len(a)):
    res = res * x + a[i]
print(res)


""" Совпадающие полиномы - дано k полиномов степени n,
    необходимо подсчитать кол-во совпадающих с ним
"""

""" Идея - подставим конкретный Х и подсчитаем
    значения для каждого полинома за O(NK), с помощью
    словаря с ключом = значению полинома, подсчитаем
    количество сопадений
"""

# хэширование - перевод большого множества в малое

""" Проблема этого решения заключается в переполнении
    переменной или замедлении из-за длинной
    арифметики
"""

# решение - вычисление полинома по модулю

X = 7
polinom = [1, 2, 1]
HASH_CONST = 2 ** 31
res = 0
for coeff in polinom:
    res = (res * X + coeff) % HASH_CONST
print(res)


string = input()

pows_arr = [X ** i % HASH_CONST for i in range(len(string))]
prefix_arr = [0] * (len(string) + 1)

# создаем префикс сумму для каждого символа строки
for i in range(1, len(string) + 1):
    prefix_arr[i] = prefix_arr[i - 1] * X + (ord(string[i - 1]) - ord('a') + 1)

def compareSubstr(s: str, l: int, first: int, second: int) -> str:
    global prefix_arr, pows_arr
    if (prefix_arr[first + l] + prefix_arr[second] * pows_arr[l]) % HASH_CONST == (prefix_arr[second + l] + prefix_arr[first] * pows_arr[l]) % HASH_CONST:
        return "yes"
    return "no"

n = int(input())
for i in range(n):
    print(compareSubstr(string, *list(map(int, input().split()))))


