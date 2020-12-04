from sys import argv
import random


def main():
  random.seed(argv[-1])
  randr = random.randrange

  n0, n1, nq0, nq1, *_ = map(int, argv[1:])
  n = randr(n0, n1)
  nq = randr(nq0, nq1)

  ls = [0] * n
  for i in range(n):
    ls[i] = randr(0, n)

  qs = [0] * nq
  for i in range(nq):
    # Only reverse/affine/sum
    t = randr(2, 5)
    l = randr(0, n)
    r = randr(l + 1, n + 1)
    if t == 0: # insert
      q = []
    if t == 1: # erase
      q = []
    if t == 2: # reverse
      q = [l, r]
    if t == 3: # affine
      q = [l, r, randr(0, 10), randr(0, 10)]
    if t == 4: # sum
      q = [l, r]
    qs[i] = [t, *q]

  print(n, nq)
  print(*ls)
  for q in qs:
    print(*q)


main()
