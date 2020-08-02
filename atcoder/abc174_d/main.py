# AFTER EDITORIAL


def solve(ls):
    n = len(ls)
    num_w = len([x for x in ls if x == "W"])
    num_r = n - num_w
    left_w = 0
    right_r = num_r
    result = num_r
    for i in range(n):
        if ls[i] == "W":
            left_w += 1
        else:
            right_r -= 1
        result = min(result, max(left_w, right_r))
    return result


def main(istr, ostr):
    (n,) = list(map(int, istr.readline().strip().split()))
    s = istr.readline().strip()
    result = solve(s)
    print(result, file=ostr)


if __name__ == "__main__":
    import sys

    main(sys.stdin, sys.stdout)


import unittest
import io, sys


class Test(unittest.TestCase):
    def test_1(self):
        inp = """\
8
WRWWRWRR
"""
        outp = """\
3
"""
        ostr = io.StringIO()
        main(io.StringIO(inp), ostr)
        self.assertEqual(ostr.getvalue(), outp)

    def test_2(self):
        inp = """\
8
RR
"""
        outp = """\
0
"""
        ostr = io.StringIO()
        main(io.StringIO(inp), ostr)
        self.assertEqual(ostr.getvalue(), outp)

    def test_3(self):
        inp = """\
4
WWRR
"""
        outp = """\
2
"""
        ostr = io.StringIO()
        main(io.StringIO(inp), ostr)
        self.assertEqual(ostr.getvalue(), outp)
