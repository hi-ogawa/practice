def main(istr, ostr):
    a = int(istr.readline())
    print(a + a * (a + a * a), file=ostr)


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
10
"""
        main(io.StringIO(inp), sys.stdout)
