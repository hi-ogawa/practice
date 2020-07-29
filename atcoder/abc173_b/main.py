def main(istr, ostr):
    n = int(istr.readline())
    types = ["AC", "WA", "TLE", "RE"]
    counts = dict((t, 0) for t in types)
    for i in range(n):
        t = istr.readline().strip()
        counts[t] += 1
    for k, v in counts.items():
        print(f"{k} x {v}", file=ostr)


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
6
AC
TLE
AC
AC
WA
TLE
"""
        main(io.StringIO(inp), sys.stdout)
