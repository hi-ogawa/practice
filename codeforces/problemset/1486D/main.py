# AFTER EDITORIAL

from sys import stdin
import os
from copy import copy

dbg = os.getenv("DEBUG")
read_tokens = lambda: stdin.readline().split()


def main_case() -> None:
    n, k = map(int, read_tokens())  # [1, 2 x 10^5]
    ls = list(map(int, read_tokens()))  # [1, n]

    def evaluate(a: int) -> bool:
        if dbg:
            print(f"=== ({a = }) ===")

        xs = [1 if a <= x else -1 for x in ls]

        ys = [0] * (n + 1)
        for i in range(n):
            ys[i + 1] = ys[i] + xs[i]

        zs = copy(ys)
        for i in range(n):
            zs[i + 1] = min(zs[i + 1], zs[i])

        for i in range(k, n + 1):
            y = ys[i]
            z = zs[i - k]
            w = y - z
            if w > 0:
                if dbg:
                    print(f"{xs = }")
                    print(f"{ys = }")
                    print(f"{zs = }")
                    print(f"{i = }, {y = }, {z = }")
                return True

        return False

    def search() -> int:
        x0 = 1
        x1 = n + 1
        while x0 + 1 < x1:
            x = (x0 + x1) // 2
            if dbg:
                print(x0, x1, x, evaluate(x))
            if evaluate(x):
                x0 = x
            else:
                x1 = x
        return x0

    res = search()
    print(res)


def main() -> None:
    main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py codeforces/problemset/1486D/main.py

%%%% begin
5 3
1 2 3 2 1
%%%%
2
%%%% end

%%%% begin
4 2
1 2 3 4
%%%%
3
%%%% end
"""
