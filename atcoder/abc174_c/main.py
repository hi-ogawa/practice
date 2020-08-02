# AFTER CONTEST


def solve(n):
    if n % 7 == 0:
        n //= 7

    if n % 2 == 0 or n % 5 == 0:
        return -1

    # Since R(k) = 1...1 = (10^k - 1) / 9, we have
    #   n | R(k)
    #   <=> 10^k = 1 ∈ Z_9n
    n9 = n * 9
    d = 10 % n9
    for i in range(n9):
        if d == 1:
            return i + 1
        d = (10 * d) % n9
    raise RuntimeError()


def main(istr, ostr):
    (k,) = list(map(int, istr.readline().strip().split()))
    result = solve(k)
    print(result, file=ostr)


if __name__ == "__main__":
    import sys

    main(sys.stdin, sys.stdout)


import unittest
import io, sys


class Test(unittest.TestCase):
    def test_1(self):
        inp = """\
101
"""
        outp = """\
4
"""
        ostr = io.StringIO()
        main(io.StringIO(inp), ostr)
        self.assertEqual(ostr.getvalue(), outp)

    def test_2(self):
        inp = """\
999983
"""
        outp = """\
999982
"""
        ostr = io.StringIO()
        main(io.StringIO(inp), ostr)
        self.assertEqual(ostr.getvalue(), outp)

    def test_3(self):
        inp = """\
2
"""
        outp = """\
-1
"""
        ostr = io.StringIO()
        main(io.StringIO(inp), ostr)
        self.assertEqual(ostr.getvalue(), outp)
