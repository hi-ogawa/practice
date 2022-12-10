# AC

import os
from sys import stdin
from typing import Callable, List

dbg = bool(os.getenv("DEBUG"))
read_tokens: Callable[[], List[str]] = lambda: stdin.readline().split()


def main_case() -> None:
    # ~ 10^18
    a, b = map(int, read_tokens())

    # given
    #   f(x) = a (x + 1)^(-1/2) + b x
    # we have
    #   f'(x) = - (a / 2) (x + 1)^(-3/2) + b  (monotonically increasing)
    #   f'(x) = 0  \iff  x = (2b / a)^(- 2 / 3) - 1

    # probably solving `x = (2b / a)^(- 2 / 3) - 1` doesn't hold enough integral-part of precision in f64
    # so we find minimum exploiting convexity

    def find_convext_min(f: Callable[[int], float]) -> int:
        x0 = 0
        x1 = 10**15  # > 10**18 ** (2 / 3)
        while x0 + 2 < x1:
            z0 = x0 + (x1 - x0) // 3
            z1 = z0 + (x1 - x0) // 3
            if f(z0) < f(z1):
                x1 = z1
            else:
                x0 = z0
        return min([x0, x0 + 1], key=lambda x: f(x))

    def f(x: int) -> float:
        return a / ((x + 1) ** (1 / 2)) + b * x

    def dbg_solve() -> float:
        return (2 * b / a) ** (-2 / 3) - 1

    x = find_convext_min(f)
    result = f(x)
    if dbg:
        print(f"{x = }, {f(x) = }, {dbg_solve() = }")
    print(result)


def main() -> None:
    main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py atcoder/abc279/d/main.py

%%%% begin
10 1
%%%%
7.7735026919
%%%% end

%%%% begin
5 10
%%%%
5.0000000000
%%%% end

%%%% begin
1000000000000000000 100
%%%%
8772053214538.5976562500
%%%% end
"""
