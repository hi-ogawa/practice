#
# PROP.
#  Existance by construction.
#


def solve(ls):
    lim = max(ls) + 1
    flip = {"x": "y", "y": "x"}
    result = []

    # s_1
    s = "x" * lim
    result += [s]

    for a in ls:
        # s_i-1 ==> s_i
        s = s[:a] + (flip[s[a]] * (lim - a))
        result += [s]

    return result


def main(istr, ostr):
    t = int(istr.readline())
    for _ in range(t):
        n = int(istr.readline())
        ls = list(map(int, istr.readline().split()))
        result = solve(ls)
        print(*result, file=ostr, sep="\n")


if __name__ == "__main__":
    import sys

    main(sys.stdin, sys.stdout)


# python -m unittest codeforces/ex1384A/main.py
import unittest


class Test(unittest.TestCase):
    def test(self):
        import io, sys

        inp = """\
4
4
1 2 4 2
2
5 3
3
1 3 1
3
0 0 0
"""
        main(io.StringIO(inp), sys.stdout)
