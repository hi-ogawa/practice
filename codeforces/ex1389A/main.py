def solve(l, r):
    if 2 * l <= r:
        return [l, 2 * l]
    return [-1, -1]


def main(istr, ostr):
    t = int(istr.readline())
    for _ in range(t):
        l, r = list(map(int, istr.readline().strip().split()))
        result = solve(l, r)
        print(*result, file=ostr)


if __name__ == "__main__":
    import sys

    main(sys.stdin, sys.stdout)


import unittest
import io, sys


class Test(unittest.TestCase):
    def test_1(self):
        inp = """\
4
1 1337
13 69
2 4
88 89
"""
        main(io.StringIO(inp), sys.stdout)
