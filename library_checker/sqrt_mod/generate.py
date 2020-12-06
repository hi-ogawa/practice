from sys import argv
import random

def make_primes(n):
  from math import isqrt
  sieve = [1] * (n + 1)
  for p in range(2, isqrt(n) + 1):
    if not sieve[p]: continue
    for x in range(p * p, n + 1, p):
      sieve[x] = 0
  res = []
  for p in range(2, n + 1):
    if sieve[p]:
      res.append(p)
  return res


def main():
  random.seed(argv[-1])
  randr = random.randrange

  t, n, *_ = map(int, argv[1:])
  primes = make_primes(n)

  print(t)
  for _ in range(t):
    p = random.choice(primes)
    y = randr(0, p)
    print(y, p)


main()
