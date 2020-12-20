from sys import argv
import random


def main():
  random.seed(argv[-1])
  randr = random.randrange

  n0, n1, k0, k1, *_ = map(int, argv[1:])
  n = randr(n0, n1)
  m = randr(n0, n1)
  k = randr(k0, k1)

  ls = [0] * k
  for i in range(k):
    ls[i] = randr(1, n + 1), randr(1, m + 1)

  print(n, m, k)
  for x, y in ls:
    print(x, y)


main()
