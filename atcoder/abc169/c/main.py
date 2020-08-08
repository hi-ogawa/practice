# Virtual, AC


def main(istr, ostr):
    x, y = istr.readline().strip().split()
    a = int(x)
    b0, _, b1, b2 = y
    b0, b1, b2 = list(map(int, [b0, b1, b2]))

    c = a * (100 * b0 + 10 * b1 + b2)
    res = c // 100
    print(res, file=ostr)


if __name__ == "__main__":
    import sys

    main(sys.stdin, sys.stdout)


import unittest
import io, sys


# python -m unittest atcoder/abc169/c/main.py
class Test(unittest.TestCase):
    def test_0(self):
        pass

    def test_1(self):
        inp = """\
1000000000000000 9.99
"""
        outp = """\
9990000000000000
"""
        ostr = io.StringIO()
        main(io.StringIO(inp), ostr)
        self.assertEqual(ostr.getvalue(), outp)

    def test_2(self):
        inp = """\
198 1.10
"""
        outp = """\
217
"""
        ostr = io.StringIO()
        main(io.StringIO(inp), ostr)
        self.assertEqual(ostr.getvalue(), outp)
