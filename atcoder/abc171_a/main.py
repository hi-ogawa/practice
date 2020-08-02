def main(istr, ostr):
    s = istr.readline().strip()
    if "a" <= s and s <= "z":
        print("a", file=ostr)
    else:
        print("A", file=ostr)


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
a
"""
        outp = """\
a
"""
        ostr = io.StringIO()
        main(io.StringIO(inp), ostr)
        self.assertEqual(ostr.getvalue(), outp)
