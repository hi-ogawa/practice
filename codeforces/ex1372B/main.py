#
# PROP.
#   Given
#     n = a + b
#     a = g a' >= 1
#     b = g b' >= 1
#     g = gcd(a, b)
#     lcm(a, b) = g a' b'
#   We have
#     g < n
#     g | (n - g)
#     lcm(a, b) >= lcm(g, n - g) = n - g
#
#   PROOF
#     Since n = a + b = g (a' + b'), clearly g < n and g | n and thus g | (n - g).
#     Then
#       lcm(g, n - g) = n - g = g (a' + b' - 1) <= g (a' b') = lcm(a, b)
#     Since
#        a' b' - ((a' + b') - 1) = (a' - 1) (b' - 1) >= 0
#
#
# REMARK.
#   From above PROP, it suffices to enumerate (a, b) of the form (q, k q) with q + k q = (1 + k) q = n.
#   For such q, it's clear that,
#     lcm(q, k q) = k q = n - q
#   Thus, largest such q (i.e. smallest p = n / q) gives min lcm(a, b).
#


def solve(n):
    p = n

    for i in range(2, n):
        if i * i > n:
            break

        if n % i == 0:
            p = i
            break

    a = n // p
    b = n - a
    return [a, b]


def main(istr, ostr):
    t = int(istr.readline())
    for _ in range(t):
        n = int(istr.readline())
        [a, b] = solve(n)
        print(f"{a} {b}", file=ostr)


if __name__ == "__main__":
    import sys

    main(sys.stdin, sys.stdout)


#
# python -m unittest codeforces/ex1372B/main.py -v
#
import unittest


class Test(unittest.TestCase):
    def test(self):
        import io, sys

        inp = """\
3
4
6
9
"""
        main(io.StringIO(inp), sys.stdout)
