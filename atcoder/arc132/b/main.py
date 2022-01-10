# AC

import os
from sys import stdin
from typing import Callable, List

dbg = bool(os.getenv("DEBUG"))
read_tokens: Callable[[], List[str]] = lambda: stdin.readline().split()


def main_case() -> None:
    (n,) = map(int, read_tokens())  # [2, 10^5]
    ls = list(map(int, read_tokens()))

    #
    # The number of reachable configurations is only `2n`.
    # They are connected as:
    #
    #   P1 <- P2 <- ... <- Pn (<- P1)
    #   ⇕     ⇕            ⇕
    #   Qn -> Q2 -> ... -> Q1 (-> Qn)
    #
    #  where
    #     Pi = ..., n, 1, 2, ...
    #                 ^^ (i-th)
    #
    #     Qi = ..., 2, 1, n, ...
    #                 ^^ (i-th)
    #

    if n == 2:
        # special case where only `n` states
        res = 1

    else:
        i = ls.index(1)
        is_p = ls[(i + 1) % n] == 2

        if is_p:
            res = min(i, n - i + 2)

        else:
            j = n - 1 - i
            res = min(j + 1, n - j + 1)

    print(res)


def main() -> None:
    main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py atcoder/arc132/b/main.py
make black isort mypy SRC=atcoder/arc132/b/main.py

%%%% begin
3
1 3 2
%%%%
2
%%%% end
"""
