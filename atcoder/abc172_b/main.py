def solve(s1, s2):
    n = len(s1)
    c = 0
    for i in range(n):
        c += s1[i] != s2[i]
    return c


def main(istr, ostr):
    s1 = istr.readline().strip()
    s2 = istr.readline().strip()
    result = solve(s1, s2)
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
cupofcoffee
cupofhottea
"""
        main(io.StringIO(inp), sys.stdout)
