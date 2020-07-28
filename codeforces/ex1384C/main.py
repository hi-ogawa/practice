def solve(n, s1, s2):
    m = 20

    # Convert to numeric
    s1 = [ord(c) - ord("a") for c in s1]
    s2 = [ord(c) - ord("a") for c in s2]

    # Make source-target transition grid
    A = [[0] * m for _ in range(m)]
    for i in range(n):
        if s1[i] > s2[i]:
            return -1
        A[s1[i]][s2[i]] = 1

    # Transform edge to make more factored edges
    #   i --> j         ===>   i --> j
    #   i --------> k   ===>         j --> k
    for i in range(m):
        for j in range(i + 1, m):
            for k in range(j + 1, m):
                if A[i][j] & A[i][k]:
                    A[i][k] = 0
                    A[j][k] = 1

    # Make reachability (closure)
    B = [[0] * m for _ in range(m)]
    for k in range(1, m):
        for i in range(k)[::-1]:
            for j in range(i, k):
                B[i][k] = A[i][k] | (B[i][j] & B[j][k])

    # Remove factored edge
    #   i --> j --> k
    #   i --------> k [REMOVE]
    for i in range(m):
        for j in range(i + 1, m):
            for k in range(j + 1, m):
                if B[i][j] & B[j][k]:
                    A[i][k] = 0

    # Count necessarily transition
    count = 0
    for i in range(m):
        for j in range(i + 1, m):
            if A[i][j]:
                count += 1
    return count


def main(istr, ostr):
    t = int(istr.readline())
    for _ in range(t):
        n = int(istr.readline())
        s1 = istr.readline().strip()
        s2 = istr.readline().strip()
        result = solve(n, s1, s2)
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
3
aab
bcc
4
cabc
abcb
3
abc
tsr
4
aabd
cccd
5
abcbd
bcdda
"""
        main(io.StringIO(inp), sys.stdout)

    def test_2(self):
        s1 = "abca"
        s2 = "bcdd"
        n = len(s1)
        print(solve(n, s1, s2))

    def test_3(self):
        # a -> b
        # a -> b -> c
        #      b -> c -> d
        #           c -> d
        s1 = "aabc"
        s2 = "bcdd"
        n = len(s1)
        print(solve(n, s1, s2))
