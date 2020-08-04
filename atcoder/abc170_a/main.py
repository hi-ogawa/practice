def main(istr, ostr):
    ls = list(map(int, istr.readline().strip().split()))
    for i in range(5):
        if ls[i] == 0:
            print(i + 1, file=ostr)


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
1 2 0 4 5
"""
        outp = """\
3
"""
        ostr = io.StringIO()
        main(io.StringIO(inp), ostr)
        self.assertEqual(ostr.getvalue(), outp)
