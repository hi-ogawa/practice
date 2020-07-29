# AFTER EDITORIAL

#
# PROP.
#   Subgraph of tree is forest.
#
# PROP.
#   For forest,
#     <num-verts> = <num-edges> + <num-components>
#   since for each component,
#     Vc = Ec + 1.
#
# PROP.
#   result = \sum_{i <= j} num_components(i, j)
#          = \sum num_verts(i, j) - num_edges(i, j)
#          = (\sum num_verts(i, j)) - (\sum num_edges(i, j))
#
#   \sum num_verts(i, j) = 1 + .. + (n-1) + n +
#                          1 + .. + (n-1) +
#                          ... +
#                          1
#                        = (tetrahedral number) = binom(n + 2, 3)
#
#   \sum num_edges(i, j) = \sum_e |{(i, j) | e in [i, j]}|
#                        = \sum_e (i0 * (n + 1 - j0))  (where e = (i0, j0))
#


def solve(ls, debug=0):
    n = len(ls) + 1
    term1 = ((n + 2) * (n + 1) * n) // 6  # 1st term in above PROP
    term2 = 0  # 2nd term in above PROP
    for i, j in ls:
        if i > j:
            i, j = j, i
        term2 += i * (n + 1 - j)

    return term1 - term2


def main(istr, ostr):
    n = int(istr.readline())
    ls = []
    for i in range(n - 1):
        v1, v2 = list(map(int, istr.readline().strip().split()))
        ls.append([v1, v2])
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
3
1 3
2 3
"""
        main(io.StringIO(inp), sys.stdout)

    def test_2(self):
        inp = """\
10
5 3
5 7
8 9
1 9
9 10
8 4
7 4
6 10
7 2
"""
        main(io.StringIO(inp), sys.stdout)
