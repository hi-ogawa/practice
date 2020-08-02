# AFTER EDITORIAL

#
# Given
#  - fixed alphabets
#  - n
#  - (b1, ... bm)
# Count
#  {(a, ... an) | (b1, ... bm) is subsequence of (a1, .., an) }
#


def compute_direct(n, m, l):
    import math

    result = 0
    for i in range(m, n + 1):
        c = math.comb(i - 1, m - 1)
        d = (l - 1) ** (i - m)
        e = l ** (n - i)
        result += c * d * e
    return result


def solve(k, s):
    modulo = 10 ** 9 + 7
    l = 26  # alphabets
    m = len(s)  # > 0
    n = k + m

    # [ Compute directly ]
    return compute_direct(n, m, l) % modulo


def main(istr, ostr):
    (k,) = list(map(int, istr.readline().strip().split()))
    s = istr.readline().strip()
    result = solve(k, s)
    print(result, file=ostr)


if __name__ == "__main__":
    import sys

    main(sys.stdin, sys.stdout)


import unittest
import io, sys


class Test(unittest.TestCase):
    def test_1(self):
        inp = """\
5
oof
"""
        outp = """\
575111451
"""
        ostr = io.StringIO()
        main(io.StringIO(inp), ostr)
        self.assertEqual(ostr.getvalue(), outp)

    def test_2(self):
        inp = """\
37564
whydidyoudesertme
"""
        outp = """\
318008117
"""
        ostr = io.StringIO()
        main(io.StringIO(inp), ostr)
        # self.assertEqual(ostr.getvalue(), outp)
