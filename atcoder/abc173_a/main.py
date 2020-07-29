def solve(n, debug=0):
    m = 1000
    r = n % m
    return 0 if r == 0 else m - r


def main(istr, ostr):
    n = int(istr.readline())
    print(solve(n), file=ostr)


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
1900
"""
        main(io.StringIO(inp), sys.stdout)
