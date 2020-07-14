#
# REMARK
#   - Define S: n symmetric group
#   - Define K ⊂ S: special exchanges = {p | ∃i0, i1. ∀i ∈ [i0, i1]. p(i) != i }
#   - Clearly id ∉ K
#
# PROP
#   ∀p ∈ S.
#      - p = id ∉ K  XOR
#      - p ∈ K  XOR
#      - p ∉ K and p = q1.q2 for q1, q2 ∈ K
#
#   PROOF (see tutorial https://codeforces.com/blog/entry/79974?f0a28=1)
#


# By above PROP, it suffices to check if ls = id or ls ∈ K
def solve(n, ls):
    k = 0
    e = True
    for i in range(n):
        ex = ls[i] == i + 1
        if e and not ex:
            k += 1
            if k == 2:
                break
        e = ex
    return k


def main(istr, ostr):
    t = int(istr.readline())
    for _ in range(t):
        n = int(istr.readline())
        ls = list(map(int, istr.readline().split()))
        print(solve(n, ls), file=ostr)


if __name__ == "__main__":
    import sys

    main(sys.stdin, sys.stdout)


import unittest


class Test(unittest.TestCase):
    def test(self):
        import io, sys

        inp = """\
2
5
1 2 3 4 5
7
3 2 4 5 1 6 7
"""
        main(io.StringIO(inp), sys.stdout)
