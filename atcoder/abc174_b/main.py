def main(istr, ostr):
    n, d = list(map(int, istr.readline().strip().split()))
    d2 = d ** 2
    c = 0
    for i in range(n):
        x, y = list(map(int, istr.readline().strip().split()))
        if x ** 2 + y ** 2 <= d2:
            c += 1
    print(c, file=ostr)


if __name__ == "__main__":
    import sys

    main(sys.stdin, sys.stdout)


import unittest
import io, sys


class Test(unittest.TestCase):
    def test_1(self):
        inp = """\
999983
"""
        outp = """\
999982
"""
        ostr = io.StringIO()
        main(io.StringIO(inp), ostr)
        self.assertEqual(ostr.getvalue(), outp)
