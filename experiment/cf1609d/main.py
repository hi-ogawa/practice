# AC

from sys import stdin, stdout
import os

dbg = os.getenv("DEBUG")


class Dsu:
    def __init__(self, n: int) -> None:
        self.parents = list(range(n))
        self.sizes = [1] * n

    def find(self, x: int) -> int:
        if self.parents[x] == x:
            return x
        self.parents[x] = self.find(self.parents[x])
        return self.parents[x]

    def merge(self, x: int, y: int) -> None:
        x = self.find(x)
        y = self.find(y)
        if x == y:
            return
        if self.sizes[x] > self.sizes[y]:
            x, y = y, x
        self.parents[x] = y
        self.sizes[y] += self.sizes[x]
        self.sizes[x] = 0


def main() -> None:
    n, d = map(int, stdin.readline().split())

    dsu = Dsu(n)
    num_components = n

    for i in range(d):
        x, y = map(int, stdin.readline().split())
        x -= 1
        y -= 1
        x = dsu.find(x)
        y = dsu.find(y)
        if x != y:
            dsu.merge(x, y)
            num_components -= 1

        # Connect larger `num_edges_left` components
        num_edges = i + 1
        num_edges_base = n - num_components
        num_edges_left = num_edges - num_edges_base

        if dbg:
            print(f"{dsu.sizes = }")
            print(f"{num_edges = }, {num_edges_base = }, {num_edges_left = }")

        answer = sum(sorted(dsu.sizes)[-num_edges_left - 1 :]) - 1
        stdout.write(f"{answer}\n")


if __name__ == "__main__":
    main()


"""
python misc/run.py experiment/cf1609d/main.py

%%%% begin
7 6
1 2
3 4
2 4
7 6
6 5
1 7
%%%%
1
1
3
3
3
6
%%%% end

%%%% begin
10 8
1 2
2 3
3 4
1 4
6 7
8 9
8 10
1 4
%%%%
1
2
3
4
5
5
6
8
%%%% end
"""
