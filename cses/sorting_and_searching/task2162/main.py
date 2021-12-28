# AC

from sys import stdin
import os

dbg = os.getenv("DEBUG")
read_tokens = lambda: stdin.readline().split()


def main_case() -> None:
    (n,) = map(int, read_tokens())  # [1, 2 x 10^5]

    # Linked list
    # (0) -> (1) -> ... -> (n - 1) -> (0) -> ...
    parents = [i + 1 for i in range(n)]
    parents[n - 1] = 0

    x = 0
    for _ in range(n):
        print(parents[x] + 1)
        parents[x] = parents[parents[x]]
        x = parents[x]


def main() -> None:
    main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py cses/sorting_and_searching/task2162/main.py

%%%% begin
5
%%%%
2
4
1
5
3
%%%% end
"""
