def solve(ls1, ls2, debug=0):
    n = len(ls1)
    result = []
    # Align from tail (ls2[n - 1 - i:])
    for i in range(n):
        # Implicitly track ls1's state based on parity of step
        if i % 2:
            j = -1 - i // 2
            x = ls1[j] ^ 1
        else:
            j = i // 2
            x = ls1[j]
        y = ls2[-i - 1]
        if debug:
            print(f"i: {i}, j: {j}, x: {x}, y: {y}")
        if x == y:
            result.append(1)
        result.append(n - i)

    return result


def main(istr, ostr):
    t = int(istr.readline())
    for _ in range(t):
        n = int(istr.readline())
        ls1 = list(map(int, istr.readline().strip()))
        ls2 = list(map(int, istr.readline().strip()))
        result = solve(ls1, ls2)
        print(len(result), *result, file=ostr)


if __name__ == "__main__":
    import sys

    main(sys.stdin, sys.stdout)


import unittest
import io, sys


class Test(unittest.TestCase):
    def test_0(self):
        ls1 = [0, 1]
        ls2 = [1, 0]
        print(solve(ls1, ls2, debug=1))

    def test_1(self):
        inp = """\
5
2
01
10
5
01011
11100
2
01
01
10
0110011011
1000110100
1
0
1
"""
        main(io.StringIO(inp), sys.stdout)
