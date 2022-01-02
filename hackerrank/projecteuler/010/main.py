# AC

from sys import stdin
import os
from typing import List

dbg = os.getenv("DEBUG")
read_tokens = lambda: stdin.readline().split()


def make_sieve(n: int) -> List[bool]:
    res = [True] * (n + 1)
    res[0] = res[1] = False

    from math import isqrt

    for x in range(2, isqrt(n) + 1):
        if not res[x]:
            continue
        for y in range(2 * x, n + 1, x):
            res[y] = False

    return res


sums: List[int] = []


def main_precompute() -> None:
    n = 2 * 10 ** 6
    sieve = make_sieve(n)
    global sums
    sums = [i * p for i, p in enumerate(sieve)]
    for i in range(n):
        sums[i + 1] += sums[i]


def main_case() -> None:
    (n,) = map(int, read_tokens())  # [1, 10^6]
    res = sums[n]
    print(res)


def main() -> None:
    main_precompute()
    (t,) = map(int, read_tokens())
    for _ in range(t):
        main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py hackerrank/projecteuler/010/main.py

%%%% begin
2
5
10
%%%%
10
17
%%%% end


%%%% begin
1
1999999
%%%%
142913828922
%%%% end
"""
