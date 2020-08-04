def solve(x, ls):
    y = 0
    m = x
    for i in range(1, 102):
        if i in ls:
            continue
        if abs(x - i) < m:
            y = i
            m = abs(x - i)
    return y


def main(istr, ostr):
    x, n = list(map(int, istr.readline().strip().split()))
    ls = list(map(int, istr.readline().strip().split()))
    result = solve(x, ls)
    print(result, file=ostr)


if __name__ == "__main__":
    import sys

    main(sys.stdin, sys.stdout)


import unittest
import io, sys


class Test(unittest.TestCase):
    def test_1(self):
        inp = """\
6 5
4 7 10 6 5
"""
        outp = """\
8
"""
        ostr = io.StringIO()
        main(io.StringIO(inp), ostr)
        self.assertEqual(ostr.getvalue(), outp)

    def test_2(self):
        inp = """\
10 5
4 7 10 6 5
"""
        outp = """\
9
"""
        ostr = io.StringIO()
        main(io.StringIO(inp), ostr)
        self.assertEqual(ostr.getvalue(), outp)

    def test_3(self):
        inp = """\
100 0

"""
        outp = """\
100
"""
        ostr = io.StringIO()
        main(io.StringIO(inp), ostr)
        self.assertEqual(ostr.getvalue(), outp)
