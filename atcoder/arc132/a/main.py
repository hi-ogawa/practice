# AC

import os
from sys import stdin
from typing import Callable, List

dbg = bool(os.getenv("DEBUG"))
read_tokens: Callable[[], List[str]] = lambda: stdin.readline().split()


def main_case() -> None:
    (n,) = map(int, read_tokens())
    r_map = [0] + list(map(int, read_tokens()))
    c_map = [0] + list(map(int, read_tokens()))

    # Unique existence via normal form like below
    #   ....# 1
    #   ...## 2
    #   ..### 3
    #   .#### 4
    #   ##### 5
    #   12345
    #
    # Then equation for "#" is
    #   j >= - i + n + 1

    (q,) = map(int, read_tokens())
    for _ in range(q):
        i, j = map(int, read_tokens())
        i, j = r_map[i], c_map[j]
        is_black = j >= -i + n + 1
        res = "#" if is_black else "."
        print(res, end="")
    print()


def main() -> None:
    main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py atcoder/arc132/a/main.py

%%%% begin
5
5 2 3 4 1
4 2 3 1 5
7
1 5
5 1
1 1
2 2
3 3
4 4
5 5
%%%%
#.#.#.#
%%%% end
"""
