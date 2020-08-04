def solve(x, y):
    # |x| = |p + q  | = | 1 1 | |p|
    # |y|   |2p + 4q|   | 2 4 | |q|
    # <=>
    # |p| = 1/2 | 4 -1| |x|  =  (4x - y)/2
    # |q|       |-2  1| |y|     (-2x +y)/2
    p2 = 4 * x - y
    q2 = -2 * x + y
    if p2 % 2 == 0 and q2 % 2 == 0 and p2 >= 0 and q2 >= 0:
        return "Yes"
    return "No"


def main(istr, ostr):
    x, y = list(map(int, istr.readline().strip().split()))
    result = solve(x, y)
    print(result, file=ostr)


if __name__ == "__main__":
    import sys

    main(sys.stdin, sys.stdout)


import unittest
import io, sys


class Test(unittest.TestCase):
    def test_1(self):
        inp = """\
3 8
"""
        outp = """\
Yes
"""
        ostr = io.StringIO()
        main(io.StringIO(inp), ostr)
        self.assertEqual(ostr.getvalue(), outp)

    def test_2(self):
        inp = """\
2 100
"""
        outp = """\
No
"""
        ostr = io.StringIO()
        main(io.StringIO(inp), ostr)
        self.assertEqual(ostr.getvalue(), outp)
