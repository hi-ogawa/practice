# AC

import os
from math import gcd, isqrt
from sys import stdin
from typing import Callable, List, Tuple

dbg = bool(os.getenv("DEBUG"))
read_tokens: Callable[[], List[str]] = lambda: stdin.readline().split()


def main_case() -> None:
    (s,) = map(int, read_tokens())

    # From Euclid's formula,
    #   a + b + c
    #       = 2nm + (n^2 - m^2) + (n^2 + m^2)
    #       = 2n(n + m)
    #
    #   a.b.c
    #       = 2nm . (n^2 - m^2) . (n^2 + m^2)
    #       = 2nm(n^4 - m^4)
    #
    # Considering non-primitive case,
    #   ka + kb + kc= 2n(n + m)k
    #   ka.kb.kc = 2nm(n^4 - m^4)k^3

    # Solve
    #   2n(n + m)k = s
    # where
    #   n > m
    #   n or m: even
    #   gcd(n, m) = 1

    # Note that
    #   n^2 < n(n + m) < s / 2

    if s % 2 == 1:
        print(-1)
        return

    n_lim = isqrt(s // 2) + 1

    # Brute force (k, n, m)
    solutions: list[Tuple[int, int, int]] = []

    for n in range(2, n_lim):
        for m in range(1, n):
            if n & 1 and m & 1:
                continue
            if gcd(n, m) != 1:
                continue
            k, r = divmod(s, 2 * n * (n + m))
            if r == 0:
                solutions.append((k, n, m))

    if dbg:
        print(solutions)

    products = [2 * n * m * (n ** 4 - m ** 4) * k ** 3 for k, n, m in solutions]
    res = max(products, default=-1)
    print(res)


def main() -> None:
    (t,) = map(int, read_tokens())
    for _ in range(t):
        main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py hackerrank/projecteuler/009/main.py
make black isort mypy SRC=hackerrank/projecteuler/009/main.py

%%%% begin
1
1000
%%%%
31875000
%%%% end
"""
