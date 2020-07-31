def solve(n):
    import math

    n8 = math.ceil(n / 4)
    n9 = n - n8
    return ("9" * n9) + ("8" * n8)


def main(istr, ostr):
    t = int(istr.readline().strip())
    for _ in range(t):
        n = int(istr.readline().strip())
        result = solve(n)
        print(result, file=ostr)


if __name__ == "__main__":
    import sys

    main(sys.stdin, sys.stdout)


import unittest
import io, sys


class Test(unittest.TestCase):
    def test_1(self):
        inp = """\
2
1
3
"""
        main(io.StringIO(inp), sys.stdout)
