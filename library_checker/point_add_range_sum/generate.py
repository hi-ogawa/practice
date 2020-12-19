from sys import argv
import random


def main():
  random.seed(argv[-1])
  randr = random.randrange

  n0, n1, nq0, nq1, x0, x1, *_ = map(int, argv[1:])
  n = randr(n0, n1)
  nq = randr(nq0, nq1)

  ls = [0] * n
  for i in range(n):
    ls[i] = randr(x0, x1)

  qs = [0] * nq
  for i in range(nq):
    t = randr(0, 2)
    if t == 0:
      qs[i] = [t, randr(0, n), randr(x0, x1)]
    if t == 1:
      l, r = [randr(0, n - 1), randr(0, n - 1)]
      l, r = min(l, r), max(l, r)
      qs[i] = [t, l, r + 1]

  print(n, nq)
  print(*ls)
  for q in qs:
    print(*q)


main()
