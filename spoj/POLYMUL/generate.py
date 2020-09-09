def main():
  import sys, random
  random.seed(int(sys.argv[1]))
  randr = random.randrange

  # t_lim = 10
  # n_lim = 10000
  # a_lim = 1000
  t_lim = 10
  n_lim = 10
  a_lim = 10
  t = randr(1, t_lim + 1)
  print(t)
  for _ in range(t):
    n = randr(1, n_lim + 1)
    ls1 = [0] * n
    ls2 = [0] * n
    for i in range(n):
      ls1[i] = randr(a_lim + 1)
      ls2[i] = randr(a_lim + 1)
    print(n)
    print(*ls1)
    print(*ls2)


main()
