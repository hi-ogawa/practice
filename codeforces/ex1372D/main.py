#
# REMARK
#   - "alive" means an element is included in the final sum
#   - "dead" means otherwise
#   - These proposition refers to any possible configuration.
#
# PROP 1
#   No alive chain of length 3
#
#   PROOF
#     By induction
#
# PROP 2
#   No dead chain of even length
#
#   PROOF
#     Clearly no dead chain of length 2.
#     Then, by induction, no dead chain of even length.
#
# PROP 3
#   At most single alive chain of length 2
#
#   Proof
#     Consider that alive 2-chain is achieved only by the last step of operation.
#
# Prop 4
#    Any possible configuration is a subset of "alternating" configuration
#
#   Proof
#      This "global" property follows from "local" properties given by three propositions above.
#

# By Prop 4, it suffices to enumerate only "alternating" configurations
def solve(ls):
    n = len(ls)
    k = (n - 1) // 2  # n = 2k + 1

    # Initial configuration
    s = 0
    for i in range(k + 1):
        s += ls[2 * i]

    # We can enumerating all "alternating" configurations by swapping one by one
    s_max = s
    for i in range(n):
        s -= ls[(2 * i) % n]
        s += ls[(2 * i + 1) % n]
        s_max = max(s_max, s)

    return s_max


def main(istr, ostr):
    n = int(istr.readline())
    ls = list(map(int, istr.readline().split()))
    print(solve(ls), file=ostr)


if __name__ == "__main__":
    import sys

    main(sys.stdin, sys.stdout)


import unittest


class Test(unittest.TestCase):
    def test(self):
        import io, sys

        inp = """\
3
7 10 2
"""
        main(io.StringIO(inp), sys.stdout)

        inp = """\
1
4
"""
        main(io.StringIO(inp), sys.stdout)
