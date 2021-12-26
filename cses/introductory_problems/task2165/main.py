# AC

from sys import stdin
import os
from typing import List, Tuple

dbg = os.getenv("DEBUG")


def main_case() -> None:
    n = int(stdin.readline().strip())  # [1, 16]

    # Construct inductively
    # TODO: prove optimality

    res = [(0, 2)]

    for _ in range(n - 1):
        curr: List[Tuple[int, int]] = []

        # move 1, ..., k from "0" to "1"
        REMAP = [0, 2, 1]
        for x, y in res:
            curr.append((REMAP[x], REMAP[y]))

        # move k + 1 from "0" to "2"
        curr.append((0, 2))

        # move 1, ..., k from "1" to "2"
        REMAP = [1, 0, 2]
        for x, y in res:
            curr.append((REMAP[x], REMAP[y]))

        res = curr

    print(len(res))
    for x, y in res:
        print(x + 1, y + 1)


def main() -> None:
    main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py cses/introductory_problems/task2165/main.py

%%%% begin
2
%%%%
3
1 2
1 3
2 3
%%%% end
"""
