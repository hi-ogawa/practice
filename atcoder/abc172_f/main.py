# AFTER EDITORIAL


def solve(ls):
    import math

    x, y, *ls = ls
    z = x + y
    s = 0
    for a in ls:
        s ^= a

    #
    # Max a <= x  s.t.
    #   0 = NimSum(a, (x + y) - a, ls)
    # <=>
    # Max a <= x s.t.
    #   ∃b.
    #     a + b = x + y  (NOTE: a + b = a ^ b + 2 (a & b))
    #     a ^ b = NimSum(ls)
    # <=>
    # Max a <= x s.t.
    #   ∃b.
    #     a & b = (x + y - NimSum(ls)) / 2
    #     a ^ b = NimSum(ls)
    #

    #
    # Thus it amounts to solve
    #   a ^ b = s
    #   a & b = (z - s) / 2 = t
    #
    # which is bit-wise independent as
    #   a  b  ^  &
    #   0  0  0  0
    #   0  1  1  0
    #   1  0  1  0
    #   1  1  0  1
    #

    if (z - s) < 0 or (z - s) % 2 == 1:
        return -1

    t = (z - s) // 2
    s_t = s & t

    if s_t > 0 or t > x:
        return -1

    a = t
    b = t
    first_set = math.floor(math.log2(s + 1))
    for i in range(first_set + 1)[::-1]:
        k = 1 << i
        if s & k:
            if (a | k) <= x:  # Greedy is optimal
                a = a | k
            else:
                b = b | k
    if a == 0:
        return -1
    return x - a


def main(istr, ostr):
    n = int(istr.readline().strip())
    ls = list(map(int, istr.readline().strip().split()))
    result = solve(ls)
    print(result, file=ostr)


if __name__ == "__main__":
    import sys

    main(sys.stdin, sys.stdout)


import unittest
import io, sys


class Test(unittest.TestCase):
    def test_0(self):
        pass

    def test_1(self):
        inp = """\
8
10 9 8 7 6 5 4 3
"""
        main(io.StringIO(inp), sys.stdout)

    def test_2(self):
        inp = """\
3
4294967297 8589934593 12884901890
"""
        main(io.StringIO(inp), sys.stdout)

    def test_3(self):
        inp = """\
3
1 1 2
"""
        main(io.StringIO(inp), sys.stdout)
