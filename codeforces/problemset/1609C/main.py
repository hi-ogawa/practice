from __future__ import annotations

# AC

from sys import stdin
import os
from math import isqrt

dbg = os.getenv("DEBUG")


def make_sieve(n: int) -> bytearray:
    sieve = bytearray([1] * (n + 1))
    sieve[0] = sieve[1] = 0
    for x in range(2, isqrt(n) + 1):
        if not sieve[x]:
            continue
        for y in range(2 * x, n + 1, x):
            sieve[y] = 0
    return sieve


SIEVE = make_sieve(10 ** 6)


def solve(ls: list[int]) -> int:
    # Squash "1" segments and count repeat
    ys: list[list[int]] = []  # (value, repeat number)
    ys.append([ls[0], 1])

    for x in ls[1:]:
        if x == 1 and ys[-1][0] == 1:
            ys[-1][1] += 1
            continue
        ys.append([x, 1])

    result = 0
    k = len(ys)
    for i, [x, _] in enumerate(ys):
        if not SIEVE[x]:
            continue

        left = 1
        right = 1
        if i > 0:
            if ys[i - 1][0] == 1:
                left += ys[i - 1][1]
        if i < k - 1:
            if ys[i + 1][0] == 1:
                right += ys[i + 1][1]
        result += left * right - 1

    return result


def main_case() -> None:
    _, e = map(int, stdin.readline().split())  # [1, 2 x 10^5], e <= n
    ls = list(map(int, stdin.readline().split()))  # [1, 10^6]

    # solve each "e-modulo" sequence
    result = sum(solve(ls[i::e]) for i in range(e))
    print(result)


def main() -> None:
    t = int(stdin.readline())  # [1, 10^4]
    for _ in range(t):
        main_case()


if __name__ == "__main__":
    main()


"""
python misc/run.py codeforces/problemset/1609C/main.py

%%%% begin
6
7 3
10 2 1 3 1 19 3
3 2
1 13 1
9 3
2 4 2 1 1 1 1 4 2
3 1
1 1 1
4 1
1 2 1 1
2 2
1 2
%%%%
2
0
4
0
5
0
%%%% end
"""
