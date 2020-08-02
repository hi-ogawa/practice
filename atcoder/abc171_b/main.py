def main(istr, ostr):
    n, k = list(map(int, istr.readline().strip().split()))
    ls = list(map(int, istr.readline().strip().split()))
    ls.sort()
    result = sum(ls[:k])
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
5 3
50 100 80 120 80
"""
        outp = """\
210
"""
        ostr = io.StringIO()
        main(io.StringIO(inp), ostr)
        self.assertEqual(ostr.getvalue(), outp)
