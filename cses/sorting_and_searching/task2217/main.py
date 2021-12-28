# AC (pypy)

from sys import stdin
import os

dbg = os.getenv("DEBUG")
read_tokens = lambda: stdin.readline().strip().split()


def main_case() -> None:
    n, m = map(int, read_tokens())  # [1, 2 x 10^5]
    ls = [x - 1 for x in map(int, read_tokens())]  # {0, .., n - 1}

    # Index of each number
    ls_inv = [0] * n
    for i, x in enumerate(ls):
        ls_inv[x] = i

    # Check if "x" starts round
    def check(x: int) -> bool:
        return x == 0 or ls_inv[x] < ls_inv[x - 1]

    # Initial state
    res = sum(map(check, range(n)))

    # Incrementally recompute
    for _ in range(m):
        i, j = [i - 1 for i in map(int, read_tokens())]
        x = ls[i]
        y = ls[j]

        # Reset relevant numbers (x, x+1, y, y+1)
        relevants = {x, x + 1, y, y + 1}
        for z in relevants:
            if z < n:
                res -= check(z)

        # Swap
        ls[j] = x
        ls[i] = y
        ls_inv[x] = j
        ls_inv[y] = i

        # Check relevant numbers after the swap
        for z in relevants:
            if z < n:
                res += check(z)

        print(res)


def main() -> None:
    main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py cses/sorting_and_searching/task2217/main.py

python misc/run.py cses/sorting_and_searching/task2217/main.py --test "file:cses/sorting_and_searching/task2217/2.txt" --truncate 100

%%%% begin
5 3
4 2 1 5 3
2 3
1 5
2 3
%%%%
2
3
4
%%%% end
"""
