# WIP

import os
from sys import stdin
from typing import Callable, Generator, List

dbg = bool(os.getenv("DEBUG"))
read_tokens: Callable[[], List[str]] = lambda: stdin.readline().split()


def main_case() -> None:
    n, m = map(int, read_tokens())  # 1 <= n <= m <= 10

    for ls in iter_solve((1 << m) - 1, n):
        print(*[x + 1 for x in ls])


def iter_solve(s: int, k: int) -> Generator[List[int], None, None]:
    if s.bit_count() < k:
        return

    if k == 0:
        yield []
        return

    for x in iter_bits(s):
        for y in iter_solve(s & ~((1 << (x + 1)) - 1), k - 1):
            yield [x, *y]


def iter_bits(x: int) -> Generator[int, None, None]:
    while x:
        yield ctz(x)
        x = x & (x - 1)


def ctz(x: int) -> int:
    return (x & -x).bit_length() - 1


def main() -> None:
    main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py atcoder/abc263/c/main.py

%%%% begin
2 3
%%%%
1 2
1 3
2 3
%%%% end

%%%% begin
3 5
%%%%
1 2 3
1 2 4
1 2 5
1 3 4
1 3 5
1 4 5
2 3 4
2 3 5
2 4 5
3 4 5
%%%% end
"""
