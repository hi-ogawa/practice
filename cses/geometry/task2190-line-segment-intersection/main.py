# WA

import os
from sys import stdin
from typing import Callable, List, Tuple

dbg = bool(os.getenv("DEBUG"))
read_tokens: Callable[[], List[str]] = lambda: stdin.readline().split()


def det(p1: Tuple[int, int], p2: Tuple[int, int], p3: Tuple[int, int]) -> int:
    (x1, y1) = p1
    (x2, y2) = p2
    (x3, y3) = p3
    return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1)


def dot(p1: Tuple[int, int], p2: Tuple[int, int], p3: Tuple[int, int]) -> int:
    (x1, y1) = p1
    (x2, y2) = p2
    (x3, y3) = p3
    return (x2 - x1) * (x3 - x1) + (y2 - y1) * (y3 - y1)


def main_case() -> None:
    x1, y1, x2, y2, x3, y3, x4, y4 = map(int, read_tokens())
    p1 = (x1, y1)
    p2 = (x2, y2)
    p3 = (x3, y3)
    p4 = (x4, y4)

    # WC
    # det1 = det(p3, p4, p1)
    # det2 = det(p3, p4, p2)
    # det3 = det(p1, p2, p3)
    # det4 = det(p1, p2, p4)
    # if det1 * det2 <= 0 and det3 * det4 <= 0:
    #     print("YES")
    # else:
    #     print("NO")

    # WC
    # det3 = det(p1, p2, p3)
    # det4 = det(p1, p2, p4)
    # if not (det3 == 0 and det4 == 0):
    #     det1 = det(p3, p4, p1)
    #     det2 = det(p3, p4, p2)
    #     if det1 * det2 <= 0 and det3 * det4 <= 0:
    #         print("YES")
    #     else:
    #         print("NO")
    # else:
    #     dot2 = dot(p1, p2, p2)
    #     dot3 = dot(p1, p2, p3)
    #     dot4 = dot(p1, p2, p4)
    #     ok1 = det3 * det4 <= 0
    #     ok2 = 0 <= dot3 and dot3 <= dot2
    #     ok3 = 0 <= dot4 and dot4 <= dot2
    #     if ok1 and (ok2 or ok3):
    #         print("YES")
    #     else:
    #         print("NO")


def main() -> None:
    (t,) = map(int, read_tokens())
    for _ in range(t):
        main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py cses/geometry/task2190/main.py

%%%% begin
5
1 1 5 3 1 2 4 3
1 1 5 3 1 1 4 3
1 1 5 3 2 3 4 1
1 1 5 3 2 4 4 1
1 1 5 3 3 2 7 4
%%%%
NO
YES
YES
YES
YES
%%%% end

%%%% begin
1
-2 -5 7 -5 -3 -5 -4 -5
%%%%
NO
%%%% end
"""
