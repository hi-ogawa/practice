# "Win" state is recursibly defined as below
def solve(ls, debug=0):
    n = len(ls)
    win = False
    for i in range(n)[::-1]:
        if win:
            if ls[i] == 1:
                win = False
        else:
            win = True
        if debug:
            print(f"i: {i}, win: {win}")
    return win


def main(istr, ostr):
    t = int(istr.readline())
    for _ in range(t):
        n = int(istr.readline())
        ls = list(map(int, istr.readline().split()))
        result = "First" if solve(ls) else "Second"
        print(result, file=ostr)


if __name__ == "__main__":
    import sys

    main(sys.stdin, sys.stdout)


import unittest
import io, sys


class Test(unittest.TestCase):
    def test_0(self):
        ls = [1, 1, 1, 1, 1, 1, 1, 1]
        solve(ls, debug=1)

    def test_1(self):
        inp = """\
7
3
2 5 4
8
1 1 1 1 1 1 1 1
6
1 2 3 4 5 6
6
1 1 2 1 2 2
1
1000000000
5
1 2 2 1 1
3
1 1 1
"""
        main(io.StringIO(inp), sys.stdout)
