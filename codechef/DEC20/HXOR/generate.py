from sys import argv
import random


def main():
  random.seed(argv[-1])
  randr = random.randrange

  n0, n1, x0, x1, *_ = map(int, argv[1:])
  n = randr(n0, n1)
  x = randr(x0, x1)

  ls = [0] * n
  for i in range(n):
    ls[i] = randr(0, 1 << 3)

  print(1)
  print(n, x)
  print(*ls)


main()
