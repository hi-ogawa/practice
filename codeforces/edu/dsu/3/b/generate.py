from sys import argv
import random


def main():
  random.seed(argv[-1])
  randr = random.randrange

  n0, n1, m0, m1, nq0, nq1, *_ = map(int, argv[1:])
  n = randr(n0, n1)
  m = randr(m0, m1)
  nq = randr(nq0, nq1)

  edges = [0] * m
  qs = [0] * nq
  for i in range(m):
    x = randr(1, n + 1)
    y = randr(1, n + 1)
    edges[i] = [x, y]

  for i in range(nq):
    l = randr(1, m)
    r = randr(1, m)
    if l > r: l, r = r, l
    qs[i] = [l, r]

  print(n, m)
  for e in edges:
    print(*e)
  print(nq)
  for q in qs:
    print(*q)


main()
