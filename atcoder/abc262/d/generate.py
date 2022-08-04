"""
python atcoder/abc262/d/generate.py 100 > atcoder/abc262/d/data/in.txt
"""

import random
import sys


def main():
    n = int(sys.argv[1])
    print(n)
    print(" ".join(str(random.randint(0, 1000)) for _ in range(n)))


if __name__ == "__main__":
    main()
