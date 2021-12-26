# WIP

from sys import stdin
import os
from typing import List

dbg = os.getenv("DEBUG")


def main_case() -> None:
    n = int(stdin.readline().strip())  # [1, 16]
    res = ["0", "1"]
    for _ in range(n - 1):
        curr: List[str] = []
        for x in res:
            curr.append("0" + x)
        for x in reversed(res):
            curr.append("1" + x)
        res = curr
    print(*res, sep="\n")


def main() -> None:
    main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py cses/introductory_problems/task2205/main.py

%%%% begin
2
%%%%
00
01
11
10
%%%% end
"""
