def solve(n):
    a, b, c, d, e = 2 * 3, 2 * 5, 2 * 7, 3 * 5, 3 * 7
    abc = a + b + c
    if n < 1 + abc:  # 1 + 30
        return None
    if n == a + abc:  # 6 + 30
        return [a, b, d, n - (a + b + d)]
    if n == b + abc:  # 10 + 30
        return [a, c, d, n - (a + c + d)]
    if n == c + abc:  # 14 + 30
        return [a, b, e, n - (a + b + e)]
    return [a, b, c, n - abc]


def main(istr, ostr):
    t = int(istr.readline().strip())
    for _ in range(t):
        n = int(istr.readline().strip())
        result = solve(n)
        if result:
            print("YES", file=ostr)
            print(*result, file=ostr)
        else:
            print("NO", file=ostr)


if __name__ == "__main__":
    import sys

    main(sys.stdin, sys.stdout)


import unittest
import io, sys


class Test(unittest.TestCase):
    def test_1(self):
        inp = """\
8
7
23
31
36
44
100
258
40
"""
        main(io.StringIO(inp), sys.stdout)
