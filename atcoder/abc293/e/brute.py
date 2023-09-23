import os
from sys import stdin
from typing import Callable, List

dbg = bool(os.getenv("DEBUG"))
read_tokens: Callable[[], List[str]] = lambda: stdin.readline().split()


def main() -> None:
    a, x, m = map(int, read_tokens())
    y = 0
    for i in range(x):
        y += (a**i) % m
    print(y % m)


if __name__ == "__main__":
    main()
