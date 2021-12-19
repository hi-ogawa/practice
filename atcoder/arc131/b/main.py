# AC

from sys import stdin
import os
from typing import List

dbg = os.getenv("DEBUG")


def main_case() -> None:
    h, w = map(int, stdin.readline().split())  # [1, 700]
    data: List[List[int]] = []
    for _ in range(h):
        data.append(list(stdin.readline().strip()))

    if dbg:
        print(*data, sep="\n")

    # 5 coloring on max degree 4
    for i in range(h):
        for j in range(w):
            if data[i][j] != ".":
                continue
            choices = set("12345")
            if i > 0:
                choices.discard(data[i - 1][j])

            if j > 0:
                choices.discard(data[i][j - 1])

            if i < h - 1 and data[i + 1][j] != ".":
                choices.discard(data[i + 1][j])

            if j < w - 1 and data[i][j + 1] != ".":
                choices.discard(data[i][j + 1])

            assert len(choices) > 0
            data[i][j] = next(iter(choices))

    for row in data:
        print("".join(row))


def main() -> None:
    main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py atcoder/arc131/b/main.py

%%%% begin
3 3
...
...
...
%%%%
%%%% end

%%%% begin
5 7
1.2.3.4
.5.1.2.
3.4.5.1
.2.3.4.
5.1.2.3
%%%%
%%%% end
"""
