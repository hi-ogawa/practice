def main():
  import sys, random
  seed, = sys.argv[1:] or [0]
  random.seed(int(seed))
  randr = random.randrange
  rands = random.sample

  n_lim, m_lim = 8, 8
  n = randr(3, n_lim + 1)
  m = randr(3, m_lim + 1)
  nq = 8
  vs = list(range(n))

  edges = [0] * m
  for i in range(m):
    edges[i] = rands(vs, 2)  # distinct choice
    # edges[i] = randr(n), randr(n)

  qs = [0] * nq
  for i in range(nq):
    qs[i] = rands(vs, 3)  # distinct choice
    # qs[i] = randr(n), randr(n), randr(n)

  print(n, m, nq)
  for x, y in edges:
    print(x + 1, y + 1)
  for x, y, z in qs:
    print(x + 1, y + 1, z + 1)

main()
