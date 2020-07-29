# TODO:
#   - for N = 1, wins
#   - for N = 2, A1 = A2 <=> lose
#   - for N = 3, for some Ai = Aj => win
def solve(ls):
    n = len(ls)


def main(istr, ostr):
    n = int(istr.readline().strip())
    ls = list(map(int, istr.readline().strip().split()))
    result = solve(ls)
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
8
10 9 8 7 6 5 4 3
"""
        main(io.StringIO(inp), sys.stdout)
