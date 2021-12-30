# AC

from sys import stdin
import os

dbg = os.getenv("DEBUG")
read_tokens = lambda: stdin.readline().split()


def main_case() -> None:
    (n,) = map(int, read_tokens())  # [1, 10^4]

    #
    # Derive via Euler-Maclaurin for (f = x^2)
    #
    # \int_{[0, n]} f = (trapezoidal-sum)
    #                + P2 (f'(0) - f'(n))     (P2 = 1/12)
    #                - P3 (f''(0) - f''(n))   (P3 = 0)
    #
    # (trapezoidal-sum) = (0^2)/2 + 1^2 + 2^2 + ... + (n-1)^2 + (n^2)/2
    #
    # \int_{[0, n]} f = (n^3)/3
    #
    # =>
    #
    # 1^2 + 2^2 + ... + (n-1)^2 + n^2
    #   = (n^2)/2 + (n^3)/3 + n/6
    #   = (2 n^2 + 3 n + 1) n / 6

    g = (2 * n * n + 3 * n + 1) * n // 6
    h = (((n + 1) * n) // 2) ** 2
    if dbg:
        print(f"{g = }, {h = }")
    res = h - g
    print(res)


def main() -> None:
    (t,) = map(int, read_tokens())  # [1, 10^4]
    for _ in range(t):
        main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py hackerrank/projecteuler/006/main.py

%%%% begin
1
10
%%%%
2640
%%%% end

%%%% begin
1
100
%%%%
25164150
%%%% end
"""
