from sys import argv
import random


def main():
  random.seed(argv[-1])
  randr = random.randrange

  n0, n1, m0, m1, k0, k1, p0, p1, *_ = map(int, argv[1:])
  n = randr(n0, n1)
  m = randr(m0, m1)
  k = randr(k0, k1)
  p = randr(p0, p1)

  ls = [[0] * m for _ in range(n)]
  for i in range(n):
    for j in range(m):
      ls[i][j] = randr(1, 10)

  print(n, m, k, p)
  for row in ls:
    print(*row)


main()
