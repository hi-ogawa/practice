from sys import argv
import random


def main():
  random.seed(argv[-1])
  randr = random.randrange

  t0, t1, n0, n1, *_ = map(int, argv[1:])
  t = randr(t0, t1)
  print(t)

  for _ in range(t):
    n = randr(n0, n1)
    print(n)


main()
