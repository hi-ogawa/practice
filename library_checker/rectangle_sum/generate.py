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
    ls[i] = [randr(0, n), randr(0, n), randr(0, n)]

  qs = [0] * nq
  for i in range(nq):
    t = randr(2, 5)
    il = randr(0, n)
    ir = randr(il + 1, n + 1)
    jl = randr(0, n)
    jr = randr(jl + 1, n + 1)
    qs[i] = [il, jl, ir, jr]

  print(n, nq)
  for p in ls:
    print(*p)
  for q in qs:
    print(*q)


main()
