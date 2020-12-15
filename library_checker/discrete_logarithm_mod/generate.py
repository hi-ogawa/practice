from sys import argv
import random


def main():
  random.seed(argv[-1])
  randr = random.randrange

  t0, t1, m0, m1, *_ = map(int, argv[1:])
  t = randr(t0, t1)
  print(t)

  for _ in range(t):
    m = randr(m0, m1)
    a = randr(0, m)
    b = randr(0, m)
    print(a, b, m)


main()
