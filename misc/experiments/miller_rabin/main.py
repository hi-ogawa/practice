
"""
Examples:

$ python misc/experiments/miller_rabin/main.py $(( 3 * 7 * 11 ))
231 = 2^1 115 + 1
factors = [[3, 1], [7, 1], [11, 1]]
phi = 120
|witness|/|coprimes| = 110/120 = 0.9166666666666666

$ python misc/experiments/miller_rabin/main.py 582715990200677 --num-samples=1000 --no-factorize
582715990200677 = 2^2 145678997550169 + 1
|witness|/|coprimes| = 0/1000 = 0.0

Cf.
- http://www.mat.uniroma2.it/~schoof/millerrabinpom.pdf
"""

def factorize(n):
  res = []
  for p in range(2, n + 1):
    if p * p > n: break
    if n % p: continue
    e = 0
    while n % p == 0:
      n //= p
      e += 1
    res.append([p, e])
  if n >= 2:
    res.append([n, 1])
  return res


def pow_mod(x, y, m):
  res = 1 % m
  while y > 0:
    if y & 1: res = (x * res) % m
    y = y >> 1
    x = (x * x) % m
  return res


def main(n, num_samples, no_factorize):
  assert n % 2 == 1

  # n = 2^k q + 1
  q = n - 1
  k = 0
  while q % 2 == 0:
    q //= 2
    k += 1

  def check_composite(x):
    y = pow_mod(x, q, n)
    if y == 1 or y == n - 1: return False
    for i in range(k - 1):
      y = (y * y) % n
      if y == n - 1: return False
    return True

  if not no_factorize:
    factors = factorize(n)
    phi = n
    for p, e in factors:
      phi = (phi // p) * (p - 1)

  witness = []
  coprimes = []

  import math
  if num_samples == 0:
    for x in range(1, n):
      if math.gcd(x, n) > 1: continue
      coprimes.append(x)
      if check_composite(x):
        witness.append(x)
  else:
    import random
    for _ in range(num_samples):
      x = random.randrange(1, n)
      if math.gcd(x, n) > 1: continue
      coprimes.append(x)
      if check_composite(x):
        witness.append(x)

  print(f"{n} = 2^{k} {q} + 1")
  if not no_factorize:
    print(f"{factors = }")
    print(f"{phi = }")
  print(f"|witness|/|coprimes| = {len(witness)}/{len(coprimes)} = {len(witness)/len(coprimes)}")


if __name__ == '__main__':
  import sys, argparse
  parser = argparse.ArgumentParser()
  parser.add_argument("n", type=int)
  parser.add_argument("--num-samples", type=int, default=0)
  parser.add_argument("--no-factorize", action="store_true", default=False)
  sys.exit(main(**parser.parse_args().__dict__))
