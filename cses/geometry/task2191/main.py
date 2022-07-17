# WIP

import os
from sys import stdin
from typing import Callable, List

dbg = bool(os.getenv("DEBUG"))
read_tokens: Callable[[], List[str]] = lambda: stdin.readline().split()


def main_case() -> None:
    (n,) = map(int, read_tokens())  # [3, 1000]
    x1, y1 = map(int, read_tokens())
    x2, y2 = map(int, read_tokens())
    res = 0
    for _ in range(n - 2):
        x3, y3 = map(int, read_tokens())
        res += (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1)
        x2, y2 = x3, y3
    print(abs(res))


def main() -> None:
    main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py cses/geometry/task2191/main.py

%%%% begin
4
1 1
4 2
3 5
1 4
%%%%
16
%%%% end
"""
