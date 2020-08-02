# AFTER EDITORIAL


def solve(k, ls):
    n = len(ls)
    i0 = 1
    i1 = max(ls)
    i = (i0 + i1) // 2
    while i0 < i1:
        m = 0
        for a in ls:
            m += (a // i) - int(a % i == 0)
        if m <= k:
            i1 = i
            i = (i0 + i1) // 2
        else:
            i0 = i + 1
            i = (i0 + i1) // 2
    return i


def main(istr, ostr):
    n, k = list(map(int, istr.readline().strip().split()))
    ls = list(map(int, istr.readline().strip().split()))
    result = solve(k, ls)
    print(result, file=ostr)


if __name__ == "__main__":
    import sys

    main(sys.stdin, sys.stdout)


import unittest
import io, sys


class Test(unittest.TestCase):
    def test_1(self):
        inp = """\
10 10
158260522 877914575 602436426 24979445 861648772 623690081 433933447 476190629 262703497 211047202
"""
        outp = """\
292638192
"""
        ostr = io.StringIO()
        main(io.StringIO(inp), ostr)
        self.assertEqual(ostr.getvalue(), outp)
