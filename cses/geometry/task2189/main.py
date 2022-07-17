# AC

import os
from sys import stdin
from typing import Callable, List
import math

dbg = bool(os.getenv("DEBUG"))
read_tokens: Callable[[], List[str]] = lambda: stdin.readline().split()


def main_case() -> None:
    x1, y1, x2, y2, x3, y3 = map(int, read_tokens())
    #
    #   det (p2 - p1, p3 - p1)
    #
    #   = det / x2 - x1 , x3 - x1 \
    #         \ y2 - y1 , y3 - y1 /
    #
    det = (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1)
    if det == 0:
        print("TOUCH")
    elif det > 0:
        print("LEFT")
    else:
        print("RIGHT")


def main() -> None:
    (t,) = map(int, read_tokens())  # [1, 10^5]
    for _ in range(t):
        main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py cses/geometry/task2189/main.py

%%%% begin
3
1 1 5 3 2 3
1 1 5 3 4 1
1 1 5 3 3 2
%%%%
LEFT
RIGHT
TOUCH
%%%% end
"""
