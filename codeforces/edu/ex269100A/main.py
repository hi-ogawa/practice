def solve(s, debug=0):
    n = len(s)
    nn = n + 1
    _ = lambda ls, i, k: ls[i] if i < k else 0  # Safe getter with 0 for out-of-bound

    # Convert to numeric
    s = [ord(c) + 1 for c in s]

    # Suffix index which we will sort
    a = list(range(nn))

    # Prefix score
    b = [0] * nn
    b_tmp = [0] * nn

    # Initialize (1-prefix)
    a.sort(key=lambda i: _(s, i, n))
    e = _(s, a[0], n)
    score = 0
    for i in range(1, nn):
        e_i = _(s, a[i], n)
        if e_i != e:
            e = e_i
            score += 1
        b[a[i]] = score

    if debug:
        print("m: 1,", a, b)

    # Recursion (m-prefix ==>> 2m-prefix)
    m = 1
    while m < n:
        # Sort 2m-prefix using m-prefix score
        a.sort(key=lambda ai: (_(b, ai, nn) << 32) + _(b, ai + m, nn))

        # Make 2m-prefix score using m-prefix score
        e = (_(b, 0, nn), _(b, m, nn))
        score = 0
        for i in range(1, n + 1):
            e_i = (_(b, a[i], nn), _(b, a[i] + m, nn))
            if debug >= 2:
                print(f"i: {i},", a[i], e_i)
            if e_i != e:
                e = e_i
                score += 1
            b_tmp[a[i]] = score
        b, b_tmp = b_tmp, b

        m = 2 * m
        if debug:
            print(f"m: {m},", a, b)

    return a


def main(istr, ostr):
    s = istr.readline().strip()
    print(*solve(s), file=ostr)


if __name__ == "__main__":
    import sys

    main(sys.stdin, sys.stdout)


import unittest
import io, sys


class Test(unittest.TestCase):
    def test_0(self):
        s = "aaaaa"
        print(solve(s, debug=1))

    def test_1(self):
        inp = """\
ababba
"""
        main(io.StringIO(inp), sys.stdout)

    def test_2(self):
        inp = """\
ppppplppp
"""
        main(io.StringIO(inp), sys.stdout)
