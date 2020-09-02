def main():
  import random, sys
  random.seed(int(sys.argv[1]))
  randr = random.randrange

  n_lim = 1000
  n = randr(1, n_lim + 1)
  print(n)
  for _ in range(n):
    lim = 1000000
    h = randr(1, lim + 1)
    c = randr(1, h + 1)
    t = randr(c, h + 1)
    print(h, c, t)


main()
