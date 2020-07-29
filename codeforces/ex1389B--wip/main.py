# TODO: no idea
def solve(n, k, z, ls):
    pass


def main(istr, ostr):
    t = int(istr.readline())
    for _ in range(t):
        n, k, z = list(map(int, istr.readline().strip().split()))
        ls = list(map(int, istr.readline().strip().split()))
        result = solve(n, k, z, ls)
        print(result, file=ostr)


if __name__ == "__main__":
    import sys

    main(sys.stdin, sys.stdout)


import unittest
import io, sys


class Test(unittest.TestCase):
    def test_1(self):
        inp = """\
4
5 4 0
1 5 4 3 2
5 4 1
1 5 4 3 2
5 4 4
10 20 30 40 50
10 7 3
4 6 8 2 9 9 7 4 10 9
"""
        main(io.StringIO(inp), sys.stdout)
