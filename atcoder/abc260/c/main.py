# AC

import os
from sys import stdin
from typing import Callable, List

dbg = bool(os.getenv("DEBUG"))
read_tokens: Callable[[], List[str]] = lambda: stdin.readline().split()

"""
|  n-1  |        n        | n+1 |
|:-----:|:---------------:|:---:|
|       |        a        |     |
|       |                 |  b  |

                 ⇓

|  n-1  |        n        | n+1 |
|:-----:|:---------------:|:---:|
| a + b |                 |     |
|       | x a + (x + y) b |     |
"""


def main_case() -> None:
    n, x, y = map(int, read_tokens())
    a = 1
    b = 0
    for _ in range(n - 1):
        a, b = (a + b), x * a + (x + y) * b
    res = y * b
    print(res)


def main() -> None:
    main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py atcoder/abc260/c/main.py

%%%% begin
2 3 4
%%%%
12
%%%% end

%%%% begin
1 5 5
%%%%
0
%%%% end

%%%% begin
10 5 5
%%%%
3942349900
%%%% end
"""
