def solve(ls):
    n = len(ls)
    s = 0
    for i in range(n):
        s ^= ls[i]

    result = [0] * n
    for i in range(n):
        result[i] = s ^ ls[i]
    return result


def main(istr, ostr):
    (n,) = list(map(int, istr.readline().strip().split()))
    ls = list(map(int, istr.readline().strip().split()))
    result = solve(ls)
    print(*result, file=ostr)


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
20 11 9 24
"""
        outp = """\
26 5 7 22
"""
        ostr = io.StringIO()
        main(io.StringIO(inp), ostr)
        self.assertEqual(ostr.getvalue(), outp)
