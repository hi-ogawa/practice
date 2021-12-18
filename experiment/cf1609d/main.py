# AC

from sys import stdin, stdout, stderr


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

        print(f"{dsu.sizes = }", file=stderr)
        print(f"{num_edges = }, {num_edges_base = }, {num_edges_left = }", file=stderr)

        answer = sum(sorted(dsu.sizes)[-num_edges_left - 1 :]) - 1
        stdout.write(f"{answer}\n")


if __name__ == "__main__":
    main()


"""
python -m experiment.cf1609d.main < experiment/cf1609d/in.txt
"""
