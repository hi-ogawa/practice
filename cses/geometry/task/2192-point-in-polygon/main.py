# AC

import os
from sys import stdin
from typing import Callable, List
import math

dbg = bool(os.getenv("DEBUG"))
read_tokens: Callable[[], List[str]] = lambda: stdin.readline().split()


def main_case() -> None:
    n, m = map(int, read_tokens())  # ≤ 1000
    points = []
    for _ in range(n):
        points.append([*map(int, read_tokens())])
    points.append(points[0])  # wrap around

    for _ in range(m):
        a, b = map(int, read_tokens())
        res = None
        radian = 0
        for (x1, y1), (x2, y2) in zip(points[:-1], points[1:]):
            u1 = x1 - a
            v1 = y1 - b
            u2 = x2 - a
            v2 = y2 - b
            # check boundary
            det = u1 * v2 - v1 * u2
            dot = u1 * u2 + v1 * v2
            if det == 0:
                if dot <= 0:
                    res = "BOUNDARY"
                    break
                else:
                    continue
            # accumulate angle
            dot1 = u1 * u1 + v1 * v1
            dot2 = u2 * u2 + v2 * v2
            sign = 1 if det > 0 else -1
            radian += sign * math.acos(dot / math.sqrt(dot1 * dot2))
        else:
            rotation = radian / (2 * math.pi)
            if round(rotation):
                res = "INSIDE"
            else:
                res = "OUTSIDE"
        print(res)


def main() -> None:
    main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py cses/geometry/task/2192-point-in-polygon/main.py

%%%% begin
4 3
1 1
4 2
3 5
1 4
2 3
3 1
1 3
%%%%
INSIDE
OUTSIDE
BOUNDARY
%%%% end
"""
