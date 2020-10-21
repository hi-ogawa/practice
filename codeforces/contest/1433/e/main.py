from math import *

n = int(input())
k = n // 2
res = factorial(k - 1) * factorial(k - 1) * comb(2 * k - 1, k - 1)

print(res)
