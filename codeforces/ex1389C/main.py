def count_alternation(s, a, b):
    n = len(s)

    # Make "a" appears before "b" (WLOG)
    for i in range(n):
        if s[i] == a:
            break
        if s[i] == b:
            a, b = b, a
            break

    # Find right most s[i1] == "b"
    i1 = 0
    for i in range(n)[::-1]:
        if s[i] == b:
            i1 = i
            break

    # Count alternation
    flip = {a: b, b: a}
    which = a
    count = 0
    for i in range(i1 + 1):
        if s[i] == which:
            if which == b:
                count += 1
            which = flip[which]

    return 2 * count


def solve(s):
    # Convert to numeric
    s = [ord(c) - ord("0") for c in s]

    k = 10  # 10 types of element
    n = len(s)
    counts = [0] * k
    for i in range(n):
        counts[s[i]] += 1

    # 1. Single type solution
    result = max(counts)

    # 2. Two types solution by brute force
    for a in range(k):
        for b in range(a + 1, k):
            if counts[a] == 0 or counts[b] == 0:
                continue
            result = max(result, count_alternation(s, a, b))

    return n - result


def main(istr, ostr):
    t = int(istr.readline())
    for _ in range(t):
        s = istr.readline().strip()
        result = solve(s)
        print(result, file=ostr)


if __name__ == "__main__":
    import sys

    main(sys.stdin, sys.stdout)


import unittest
import io, sys


class Test(unittest.TestCase):
    def test_0(self):
        s = "252525252525"
        print(solve(s))

    def test_1(self):
        inp = """\
3
95831
100120013
252525252525
"""
        main(io.StringIO(inp), sys.stdout)
