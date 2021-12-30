# WA

from sys import stdin
import os
from typing import Literal, Tuple

dbg = os.getenv("DEBUG")
read_tokens = lambda: stdin.readline().split()

T = Tuple[int, int]
O = Literal[-1, 0, 1]

ORIGIN = (0, 0, 0)


def to_orientataion(a: T, b: T, c: T) -> O:
    x0, y0 = b[0] - a[0], b[1] - a[1]
    x1, y1 = c[0] - a[0], c[1] - a[1]
    d = x0 * y1 - x1 * y0
    if d > 0:
        return 1
    if d < 0:
        return -1
    return 0


def main_case() -> None:
    (n,) = map(int, read_tokens())

    res = 0
    for _ in range(n):
        x0, y0, x1, y1, x2, y2 = map(int, read_tokens())
        p0, p1, p2 = (x0, y0), (x1, y1), (x2, y2)
        o0 = to_orientataion(ORIGIN, p0, p1)
        o1 = to_orientataion(ORIGIN, p1, p2)
        o2 = to_orientataion(ORIGIN, p2, p0)
        # it's impossible to have o0 = o1 = o2 = 0
        res += o0 == o1 and o1 == o2

    print(res)


def main() -> None:
    main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py hackerrank/projecteuler/102/main.py

%%%% begin
2
-1 -2 1 -2 1 3
-2 -1 -2 1 -1 2
%%%%
1
%%%% end
"""
