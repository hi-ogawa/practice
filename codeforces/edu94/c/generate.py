def main():
  import sys, random
  seed = dict(enumerate(sys.argv)).get(1, 0)
  random.seed(int(seed))
  randr = random.randrange

  n_lim = 10
  n = randr(2, n_lim + 1)
  x = randr(1, n)
  ls = [0] * n
  for i in range(n):
    ls[i] = randr(2)
  print(1)
  print(*ls, sep='')
  print(x)

main()
