#
#               binom(m, n)
#  1, 2, ..., m   ==>  a1, a2, ..., an
#                                       || TODO (but not only complete shuffle, also can take from 1..m)
#                                       \/
#                      b1, b2, ..., bn
#


def binom(n, k, modulo):
    # TODO
    return 1


def solve(n, m):
    modulo = 10 ** 9 + 7
    x = binom(m, n, modulo)
    y = 1  # TODO
    return x * y


def main(istr, ostr):
    n, m = list(map(int, istr.readline().strip().split()))
    result = solve(n, m)
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
141421 356237
"""
        main(io.StringIO(inp), sys.stdout)
