# WA

# Solve the problem with "at least k distinc values"

from sys import stdin
import os
from typing import DefaultDict, Optional, Set

dbg = os.getenv("DEBUG")
read_tokens = lambda: stdin.readline().strip().split()


def main_case() -> None:
    n, k = map(int, read_tokens())
    ls = list(map(int, read_tokens()))

    #
    # Precompute closest duplicate pairs
    #

    indices_dict: DefaultDict[int, list[int]] = DefaultDict(list)
    for i, x in enumerate(ls):
        indices_dict[x].append(i)

    dup_r: list[Optional[int]] = [None] * n
    dup_l: list[Optional[int]] = [None] * n
    for indices in indices_dict.values():
        for i, j in zip(indices[:-1], indices[1:]):
            dup_r[i] = j
            dup_l[j] = i

    #
    # Incrementally compute minimal segment for each left index
    #

    # 1. initial minimal segment
    elems: Set[int] = set()
    for r, x in enumerate(ls):
        elems.add(x)
        if len(elems) == k:
            break
    else:
        print(0)
        return

    if dbg:
        print(0, r)

    res = n - r

    # 2. incrementally
    for l in range(1, n):
        dup = dup_r[l - 1]
        if dup is not None and dup <= r:
            res += n - r
            if dbg:
                print(l, r)
            continue
        for i in range(r + 1, n):
            dup = dup_l[i]
            if dup is None or dup < l:
                r = i
                res += n - r
                if dbg:
                    print(l, r)
                break
        else:
            break

    print(res)


def main() -> None:
    main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py cses/sorting_and_searching/task2428/main.py

%%%% begin
5 2
1 2 3 1 1
%%%%
10
%%%% end
"""
