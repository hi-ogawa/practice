def main():
  import sys, random
  random.seed(int(sys.argv[1]))
  randr = random.randrange

  n = 10
  nq = 10
  ls = [0] * n
  qs = [0] * nq
  for i in range(n):
    ls[i] = randr(1, 100000)
  for i in range(nq):
    qs[i] = randr(1, 3), *sorted([randr(1, n + 1), randr(1, n + 1)])

  print(n, nq)
  print(*ls)
  for q in qs:
    print(*q)

main()
