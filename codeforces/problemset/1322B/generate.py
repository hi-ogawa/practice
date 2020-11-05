def main():
  import sys, random
  random.seed(int(sys.argv[1]))
  randr = random.randrange

  n_lim = 100000
  x_lim = 10 ** 7
  n = randr(2, n_lim + 1)
  ls = [0] * n
  for i in range(n):
    ls[i] = randr(1, x_lim + 1)

  print(n)
  print(*ls)


main()
