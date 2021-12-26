# AC

from sys import stdin
import os
from typing import List
import itertools

dbg = os.getenv("DEBUG")


class Solver:
    def __init__(self, limit: int) -> None:
        #   numbers     |  #{ numbers }  |  #{ digits }
        #   1 .. 9      |   9            |  9 x 1
        #   10 .. 99    |   90           |  90 x 2
        #   100 .. 999  |   900          |  900 x 3

        cum_count: List[int] = [0]

        for i in itertools.count():
            count = 9 * (10 ** i) * (i + 1)
            count += cum_count[-1]
            cum_count.append(count)
            if count > limit:
                break

        self.cum_count = cum_count

    def solve(self, k: int) -> int:
        # Find bucket
        for i in itertools.count():
            if k < self.cum_count[i]:
                break
        i -= 1

        # Find number
        offset = k - self.cum_count[i]
        number_offset = offset // (i + 1)
        number = (10 ** i) + number_offset

        # Find digit
        digit_offset = offset % (i + 1)
        digit = str(number)[digit_offset]

        return int(digit)


def main_case() -> None:
    solver = Solver(10 ** 18)
    q = int(stdin.readline().strip())  # [1, 1000]
    for _ in range(q):
        k = int(stdin.readline().strip())  # [1, 10^18]
        res = solver.solve(k - 1)
        print(res)


def main() -> None:
    main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py cses/introductory_problems/task2431/main.py

%%%% begin
3
7
19
12
%%%%
7
4
1
%%%% end
"""
