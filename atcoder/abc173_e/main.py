# AFTER EDITORIAL, AC


def solve(ls, k, debug=0):
    modulo = 10 ** 9 + 7
    n = len(ls)
    n_neg = 0
    for i in range(n):
        n_neg += ls[i] < 0
    n_pos = n - n_neg

    # Sort by abs
    ls_abs = [abs(x) for x in ls]
    ls_abs_argsort = sorted(list(range(n)), key=lambda i: -ls_abs[i])

    # Check if positive result is impossible
    if n_neg >= k:
        positive = (k % 2 == 0) or (n_pos > 0)
    else:
        positive = (n_neg % 2 == 0) or (n > k)

    # If positive is impossible, pick "abs" small ones
    if not positive:
        p = 1
        for i in range(k):
            x = ls[ls_abs_argsort[-1 - i]]
            p *= x
            p %= modulo
        return p

    #
    # If positive is possible, ...
    #
    # PROP.
    #   At most one swap is needed for making product non-negative.
    #   PROOF. TODO
    #

    # Check sign when we pick "abs" large ones
    s = 1
    for i in range(k):
        x = ls[ls_abs_argsort[i]]
        s *= -1 if x < 0 else 1

    # If non-negative, we take as it is
    if s > 0:
        p = 1
        for i in range(k):
            x = ls[ls_abs_argsort[i]]
            p *= x
            p %= modulo
        return p

    # If negative, ...
    #   1. replace small negative with large positive, or
    #   2. replace small positive with large negative
    opt1 = None
    opt2 = None
    neg1 = pos1 = None
    pos2 = neg2 = None

    # Check if "1" is possible
    swap_pos = None
    for i in range(k, n):
        if ls[ls_abs_argsort[i]] >= 0:
            swap_pos = i
            pos1 = ls[ls_abs_argsort[i]]
            break

    swap_neg = None
    for i in range(k)[::-1]:
        if ls[ls_abs_argsort[i]] < 0:
            swap_neg = i
            neg1 = ls[ls_abs_argsort[i]]
            break

    if swap_pos is not None and swap_neg is not None:
        p = 1
        p *= ls[ls_abs_argsort[swap_pos]]
        p %= modulo
        for i in range(k):
            if i == swap_neg:
                continue
            x = ls[ls_abs_argsort[i]]
            p *= x
            p %= modulo
        opt1 = p

    # Check if "2" is possible
    swap_pos = None
    for i in range(k)[::-1]:
        if ls[ls_abs_argsort[i]] >= 0:
            swap_pos = i
            pos2 = ls[ls_abs_argsort[i]]
            break

    swap_neg = None
    for i in range(k, n):
        if ls[ls_abs_argsort[i]] < 0:
            swap_neg = i
            neg2 = ls[ls_abs_argsort[i]]
            break

    if swap_pos is not None and swap_neg is not None:
        p = 1
        p *= ls[ls_abs_argsort[swap_neg]]
        p %= modulo
        for i in range(k):
            if i == swap_pos:
                continue
            x = ls[ls_abs_argsort[i]]
            p *= x
            p %= modulo
            opt2 = p

    # Pick opt1 or opt2
    if opt1 is None:
        return opt2

    if opt2 is None:
        return opt1

    if pos1 * pos2 > neg1 * neg2:
        return opt1

    return opt2


def main(istr, ostr):
    n, k = list(map(int, istr.readline().strip().split()))
    ls = list(map(int, istr.readline().strip().split()))
    result = solve(ls, k)
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
4 2
1 2 -3 -4
"""
        main(io.StringIO(inp), sys.stdout)

    def test_2(self):
        inp = """\
4 3
-1 -2 -3 -4
"""
        main(io.StringIO(inp), sys.stdout)

    def test_3(self):
        inp = """\
2 1
-1 1000000000
"""
        main(io.StringIO(inp), sys.stdout)

    def test_4(self):
        inp = """\
10 10
1000000000 100000000 10000000 1000000 100000 10000 1000 100 10 1
"""
        main(io.StringIO(inp), sys.stdout)
