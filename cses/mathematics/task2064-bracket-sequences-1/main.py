# WIP

#
# define
#   L(i, j) = #{ TODO }
#
# then it holds that
#
#   [recursive relation]
#      L(i, j) = L(i - 1, j - 1) + L(i + 1, j - 1)
#
#   [boundary conditions]
#      L(0, 0) = 1
#      L(0, j) = 0 (for j > 0)
#
# tabulating L(i, j)
#
#     i \ j |  0  1  2...       n
#      ---
#       0      1  0  1  ..    L(0, n)  <- this is the answer
#       1         1
#       .            1
#
#   [recursive relation]
#
#              j-1,            j
#           +---------------------
#      i-1  |  L(i-1, j-1) ↘
#       i   |                L(i, j)
#      i+1  |  L(i+1, j-1) ↗
#
# we see that
#      L(0, n) = (a number of paths from (0, 0) to (0, n) by moving only "↘" or "↗" )
#              =
#

import os
from sys import stdin
from typing import Callable, List

dbg = bool(os.getenv("DEBUG"))
read_tokens: Callable[[], List[str]] = lambda: stdin.readline().split()


def pow_mod(x: int, p: int, m: int) -> int:
    res = 1
    while p > 0:
        if p & 1:
            res = res * x % m
        x = x * x % m
        p = p >> 1
    return res


M = 10**9 + 7

factorials: List[int] = None
inv_factorials: List[int] = None


def precompute_factorials(n: int) -> None:
    global factorials
    global inv_factorials
    factorials = [*range(n + 1)]
    inv_factorials = [*range(n + 1)]
    factorials[0] = 1
    inv_factorials[0] = 1
    for i in range(1, n + 1):
        factorials[i] = factorials[i - 1] * i % M
    inv_factorials[n] = pow_mod(n, M - 2, M)  # = n^(-1)
    for i in reversed(range(1, n + 1)):
        inv_factorials[i - 1] = inv_factorials[i] * i % M


def binom(n: int, m: int) -> int:
    return factorials[m] * factorials[n - m] * inv_factorials[n] % M


def main_case() -> None:
    (n,) = map(int, read_tokens())  # [1, 10^6]
    precompute_factorials(n)
    # res = 0
    # for i in range(n // 2 + 1):
    #     res += binom(n - i, i)
    #     res %= M
    # print(res)


def main() -> None:
    main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py cses/mathematics/task/2064-bracket-sequences-1/main.py

%%%% begin
6
%%%%
5
%%%% end
"""
