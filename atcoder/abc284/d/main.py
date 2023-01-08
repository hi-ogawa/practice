# AC

from itertools import count
import math
import os
from sys import stdin
from typing import Callable, List

dbg = bool(os.getenv("DEBUG"))
read_tokens: Callable[[], List[str]] = lambda: stdin.readline().split()


def main_case() -> None:
    (n,) = map(int, read_tokens())

    for p in count(2):
        if n % p == 0:
            break

    if n % (p * p) != 0:
        p = math.isqrt(n // p)

    print(p, n // p // p)


def main() -> None:
    (t,) = map(int, read_tokens())
    for _ in range(t):
        main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py atcoder/abc284/d/main.py

%%%% begin
3
2023
63
1059872604593911
%%%%
17 7
3 7
104149 97711
%%%% end
"""
