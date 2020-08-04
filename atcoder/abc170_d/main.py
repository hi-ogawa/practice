def solve(ls):
    n = len(ls)
    lim = max(ls)
    sieve = [1] * (lim + 1)
    result = 0
    ls.sort()
    for i in range(n):
        x = ls[i]
        if sieve[x] == 0:
            continue
        # Don't count if ls[i] = ls[i+1]
        if not (i + 1 < n and x == ls[i + 1]):
            result += 1
        y = x
        while y <= lim:
            sieve[y] = 0
            y += x
    return result


def main(istr, ostr):
    n = list(map(int, istr.readline().strip().split()))
    ls = list(map(int, istr.readline().strip().split()))
    result = solve(ls)
    print(result, file=ostr)


if __name__ == "__main__":
    import sys

    main(sys.stdin, sys.stdout)


import unittest
import io, sys


class Test(unittest.TestCase):
    def test_1(self):
        inp = """\
5
24 11 8 3 16
"""
        outp = """\
3
"""
        ostr = io.StringIO()
        main(io.StringIO(inp), ostr)
        self.assertEqual(ostr.getvalue(), outp)

    def test_2(self):
        inp = """\
4
5 5 5 5
"""
        outp = """\
0
"""
        ostr = io.StringIO()
        main(io.StringIO(inp), ostr)
        self.assertEqual(ostr.getvalue(), outp)

    def test_3(self):
        inp = """\
10
33 18 45 28 8 19 89 86 2 4
"""
        outp = """\
5
"""
        ostr = io.StringIO()
        main(io.StringIO(inp), ostr)
        self.assertEqual(ostr.getvalue(), outp)
