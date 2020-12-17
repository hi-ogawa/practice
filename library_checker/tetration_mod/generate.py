from sys import argv
import random


def main():
  random.seed(argv[-1])
  randr = random.randrange

  t0, t1, a0, a1, b0, b1, m0, m1, *_ = map(int, argv[1:])
  t = randr(t0, t1)

  print(t)
  for _ in range(t):
    a = randr(a0, a1)
    b = randr(b0, b1)
    m = randr(m0, m1)
    print(a, b, m)


main()
