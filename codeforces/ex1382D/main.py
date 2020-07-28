#
# Same algorithm but slower than main.js
#

#
# Partition problem (DP)
# Cf. https://en.wikipedia.org/wiki/Partition_problem
#


# O(n.m)
def find_subset_v2(ls, target):
    n = len(ls)
    m = target + 1
    dp = [[0] * m for _ in range(n)]
    dp[0][0] = 1
    if ls[0] < m:
        dp[0][ls[0]] = 1
    for i in range(1, n):
        for j in range(m):
            x = dp[i - 1][j]
            if j - ls[i] >= 0:
                x |= dp[i - 1][j - ls[i]]
            dp[i][j] = x
    return dp[n - 1][target]


#
# parition problem (Brute force)
#


def _find_subset(n0, n, ls, target):
    if n0 >= n:
        return False

    # Cull if already exceeds target
    if target < 0:
        return False

    # Found target
    if target == 0:
        return True

    # Take ls[n0]
    if _find_subset(n0 + 1, n, ls, target - ls[n0]):
        return True

    # Not take ls[n0]
    if _find_subset(n0 + 1, n, ls, target):
        return True

    return False


def find_subset(ls, target):
    return _find_subset(0, len(ls), ls, target)


def solve(ls, debug=0):
    n = len(ls)

    # Make cumulative max and indices where cummax changes
    cm = [0] * n
    cm_id = []
    m = 0
    for i in range(n):
        if ls[i] > m:
            cm_id.append(i)
            m = ls[i]
        cm[i] = m

    # Each region where cummax is same belong to same "unmerged" side
    cm_id_diff = [cm_id[i + 1] - cm_id[i] for i in range(len(cm_id) - 1)]
    cm_id_diff.append(n - cm_id[-1])

    if debug:
        print(ls, cm, cm_id, cm_id_diff)

    # Find parition which makes "unmerged" pair same length
    # return find_subset(cm_id_diff, n // 2)
    return find_subset_v2(cm_id_diff, n // 2)


def main(istr, ostr):
    t = int(istr.readline())
    for _ in range(t):
        n = int(istr.readline())
        ls = list(map(int, istr.readline().strip().split()))
        result = solve(ls)
        print("YES" if result else "NO", file=ostr)


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
6
2
2 3 1 4
2
3 1 2 4
4
3 2 6 1 5 7 8 4
3
1 2 3 4 5 6
4
6 1 3 7 4 5 8 2
6
4 3 2 5 1 11 9 12 8 6 10 7
"""
        main(io.StringIO(inp), sys.stdout)
