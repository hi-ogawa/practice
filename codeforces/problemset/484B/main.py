# WIP

from sys import stdin
import os

dbg = os.getenv("DEBUG")


def main_case() -> None:
    _ = int(stdin.readline().strip())  # [1, 2 x 10^5]
    ls_map = map(int, stdin.readline().strip().split())  # [1, 10^6]
    ls = sorted(set(ls_map))

    k = 2 * ls[-1]
    xs = [0] * k
    for x in ls:
        xs[x] = x
    for i in range(k - 1):
        xs[i + 1] = max(xs[i], xs[i + 1])

    res = 0
    for x in ls:
        for y in range(2 * x, k, x):
            res = max(res, xs[y] % x)

    print(res)


def main() -> None:
    main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py codeforces/problemset/484B/main.py

%%%% begin
3
3 4 5
%%%%
2
%%%% end
"""
