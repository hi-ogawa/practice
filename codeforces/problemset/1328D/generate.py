def main():
  import sys, random
  random.seed(sys.argv[1])
  randr = random.randrange

  t = 100
  n_lim = 6
  c_lim = 3
  print(t)
  for _ in range(t):
    n = randr(3, n_lim + 1)
    ls = [0] * n
    for i in range(n):
      ls[i] = randr(1, c_lim + 1);

    print(n)
    print(*ls, sep=' ')

main()
