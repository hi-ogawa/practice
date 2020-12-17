
"""
Example:

$ python misc/experiments/miller_rabin/main.py $(( 3 * 7 * 11 ))
231 = 2^1 115 + 1
factors = [[3, 1], [7, 1], [11, 1]]
|witness|/phi(n) = 110/120 = 0.9166666666666666

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


def main(n):
  assert n % 2 == 1

  # n = 2^k q + 1
  q = n - 1
  k = 0
  while q % 2 == 0:
    q //= 2
    k += 1

  def check_composite(x):
    y = pow_mod(x, q, n)
    if (y - 1) % n == 0: return False
    for i in range(k):
      if (y + 1) % n == 0: return False
      y = (y * y) % n
    return True

  factors = factorize(n)
  phi = n
  for p, e in factors:
    phi = (phi // p) * (p - 1)

  witness = []
  import math
  for x in range(n):
    if math.gcd(x, n) > 1: continue
    if check_composite(x):
      witness.append(x)

  print(f"{n} = 2^{k} {q} + 1")
  print(f"{factors = }")
  print(f"|witness|/phi(n) = {len(witness)}/{phi} = {len(witness)/phi}")


if __name__ == '__main__':
  import sys, argparse
  parser = argparse.ArgumentParser()
  parser.add_argument("n", type=int)
  sys.exit(main(**parser.parse_args().__dict__))
