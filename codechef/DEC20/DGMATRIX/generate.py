from sys import argv
import random


def main():
  random.seed(argv[-1])
  randr = random.randrange

  n0, n1, *_ = map(int, argv[1:])
  n = randr(n0, n1)

  xs = [[0] * (n + 1) for _ in range(n + 1)]
  ys = [[0] * n for _ in range(n)]
  for i in range(n + 1):
    for j in range(n + 1):
      xs[i][j] = randr(0, 10)
  for i in range(n):
    for j in range(n):
      ys[i][j] = xs[i][j] + xs[i + 1][j] + xs[i][j + 1] + xs[i + 1][j + 1]

  print(n)
  for y in ys:
    print(*y)


main()
