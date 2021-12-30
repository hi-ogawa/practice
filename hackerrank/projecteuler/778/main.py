# WIP

from sys import stdin
import os
from typing import List
from copy import copy

DEBUG = os.getenv("DEBUG")
read_tokens = lambda: stdin.readline().split()

MODULO = 10 ** 9 + 9

def main_case() -> None:
    r, m = map(int, read_tokens())  # < 10^6

    # For simplicity, consider half open interval [0, m)
    m += 1

    # Digit length
    n = len(str(m))

    # Digit statistics for each position of the numbers [0, m)
    #   stats(k, d)
    stats: List[List[int]] = [[0] * 10 for _ in range(n)]
    for k in range(n):
        ten_k = 10 ** k
        ten_k_one = 10 ** (k + 1)
        base = (m // ten_k_one) * ten_k
        bonus1 = ten_k
        bonus2 = m % ten_k
        d_lim = (m % ten_k_one) // ten_k
        for d in range(10):
            stats[k][d] += base
            if d < d_lim:
                stats[k][d] += bonus1
            elif d == d_lim:
                stats[k][d] += bonus2

    if DEBUG:
        print("--- stats ---")
        print(*stats, sep="\n")

    # Digit statistics for each position of freshman's product
    #   stats2(k, r, d) = #{ ... }
    stats2: List[List[List[int]]] = [[[0] * 10 for _ in range(r + 1)] for _ in range(n)]

    if DEBUG:
        print(f"{n = }, {r = }")

    for k in range(n):
        if DEBUG:
            print(f"{k = }")

        # dp(r, d)
        dp = stats2[k]
        st = stats[k]
        dp[1] = copy(st)
        for i in range(1, r):
            for d1 in range(10):
                c1 = st[d1]
                for d2 in range(10):
                    c2 = dp[i][d2]
                    d3 = (d1 * d2) % 10
                    dp[i + 1][d3] += c1 * c2
                    dp[i + 1][d3] %= MODULO

    # Take sum for each position
    res = 0
    for k in range(n):
        for d in range(10):
            res += d * stats2[k][r][d] * 10 ** k
            res %= MODULO
    print(res)

def main() -> None:
    main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py hackerrank/projecteuler/778/main.py

%%%% begin
2 7
%%%%
204
%%%% end

%%%% begin
23 76
%%%%
5870548
%%%% end
"""
