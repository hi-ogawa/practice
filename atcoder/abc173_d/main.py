#
# PROP.
#   At most once, the largest element can be included in the sum.
#
# PROP. (TODO: not really true. want to add more constraints.)
#   At most twice, each element can be included in the sum.
#
# PROP.
#   From above two PROP, "solve" is optimal.
#


def solve(ls, debug=0):
    n = len(ls)
    ls = sorted(ls)
    result = 0
    # Pick once largest
    if n >= 2:
        result += ls[-1]
    # Pick twice for each next larger one
    for i in range(2, n):
        result += ls[-1 - i // 2]
    return result


def main(istr, ostr):
    n = int(istr.readline())
    ls = list(map(int, istr.readline().strip().split()))
    print(solve(ls), file=ostr)


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
4
2 2 1 3
"""
        main(io.StringIO(inp), sys.stdout)

    def test_2(self):
        inp = """\
7
1 1 1 1 1 1 1
"""
        main(io.StringIO(inp), sys.stdout)
