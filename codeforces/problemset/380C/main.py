# TLE

from sys import stdin
import os
from typing import List, Tuple

dbg = os.getenv("DEBUG")

# paired
# unpaired left
# unpaired right
T = Tuple[int, int, int]

zero = (0, 0, 0)


def mul(x: T, y: T) -> T:
    xp, xl, xr = x
    yp, yl, yr = y
    p = min(xl, yr)
    return (xp + yp + 2 * p, xl + yl - p, xr + yr - p)


class SegmentTree:
    def __init__(self, s: str) -> None:
        n = len(s)
        n = 1 << (n.bit_length() + 1)
        self.n = n
        self.data: List[Tuple[int, int, int]] = [zero] * (2 * n)
        for i, c in enumerate(s, n):
            self.data[i] = (0, int(c == "("), int(c == ")"))

        for i in reversed(range(1, n)):
            self.data[i] = mul(self.data[2 * i], self.data[2 * i + 1])

    def reduce(self, ql: int, qr: int) -> T:
        def rec(l: int, r: int, i: int) -> T:
            if r <= ql or qr <= l:
                return zero

            if ql <= l and r <= qr:
                return self.data[i]

            m = (l + r) // 2
            res_l = rec(l, m, 2 * i)
            res_r = rec(m, r, 2 * i + 1)
            return mul(res_l, res_r)

        return rec(0, self.n, 1)

    def reduce_opt(self, ql: int, qr: int) -> T:
        l = ql + self.n
        r = qr + self.n
        res_l = zero
        res_r = zero
        while l < r:
            if l & 1:
                res_l = mul(res_l, self.data[l])
                l += 1
            if r & 1:
                r -= 1
                res_r = mul(self.data[r], res_r)
            l //= 2
            r //= 2
        return mul(res_l, res_r)


def main_case() -> None:
    s = stdin.readline().strip()
    m = int(stdin.readline().strip())
    tree = SegmentTree(s)

    for _ in range(m):
        l, r = map(int, stdin.readline().split())
        res = tree.reduce_opt(l - 1, r)
        print(res[0])


def main() -> None:
    main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py codeforces/problemset/380C/main.py

%%%% begin
())(())(())(
7
1 1
2 3
1 2
1 12
8 12
5 11
2 10
%%%%
0
0
2
10
4
6
6
%%%% end
"""
