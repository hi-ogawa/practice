#
# Generate wheel factorization constants
#

def make_primes(n):
  import math
  s = [1] * (n + 1)
  for p in range(2, math.isqrt(n) + 1):
    if not s[p]: continue
    for x in range(p * p, n + 1, p):
      s[x] = 0
  res = []
  for p in range(2, n + 1):
    if s[p]:
      res.append(p)
  return res


def main(n, debug):
  import functools
  ps = make_primes(n)
  m = functools.reduce(lambda x, y: x * y, ps)
  xs = [1] * m
  for p in ps:
    for i in range(0, m, p):
      xs[i] = 0
  ys = []
  for i in range(m):
    if xs[i]:
      ys.append(i)
  if debug:
    print(f"{ps =}")
    print(f"{len(xs) = }, {len(ys) = }")
    print(f"{xs = }")
    print(f"{ys = }")

  print(f"constexpr ll wheel_m = {m};")
  print(f"constexpr ll wheel_k = {len(ys)};")
  print(f"constexpr ll wheel_steps[wheel_k] = {{{', '.join(map(str, ys))}}};")


if __name__ == '__main__':
  import sys, argparse
  parser = argparse.ArgumentParser()
  parser.add_argument("n", type=int)
  parser.add_argument("--debug", action="store_true", default=False)
  sys.exit(main(**parser.parse_args().__dict__))
