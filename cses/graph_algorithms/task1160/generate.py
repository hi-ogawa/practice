def main():
  import sys, random
  seed, = sys.argv[1:] or [0]
  random.seed(int(seed))
  randr = random.randrange

  n_lim = 6
  n = randr(4, n_lim + 1)
  m = 4
  ls = [0] * n
  for i in range(n):
    ls[i] = randr(n) + 1
  qs = [0] * m
  for i in range(m):
    qs[i] = [randr(n) + 1, randr(n) + 1]

  print(n, m)
  print(*ls)
  for x, y in qs:
    print(x, y)


main()
