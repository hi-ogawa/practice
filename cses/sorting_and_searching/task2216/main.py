# AC

from sys import stdin
import os

dbg = os.getenv("DEBUG")


def main_case() -> None:
    n = int(stdin.readline().strip())  # [1, 2 x 10^5]
    ls = list(map(int, stdin.readline().strip().split()))
    ls = [x - 1 for x in ls]  # {0, ..., n - 1}

    #
    # PROP.
    #   "x_i" starts a round  ⇔  ∀j < i. x_j ≠ x_i - 1
    #

    ls_inv = [0] * n
    for i, x in enumerate(ls):
        ls_inv[x] = i

    res = 0
    for i, x in enumerate(ls):
        if x == 0 or i < ls_inv[x - 1]:
            res += 1

    print(res)


def main() -> None:
    main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py cses/sorting_and_searching/task2216/main.py

%%%% begin
5
4 2 1 5 3
%%%%
3
%%%% end
"""
