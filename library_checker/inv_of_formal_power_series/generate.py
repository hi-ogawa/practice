def main():
  import sys, random
  random.seed(int(sys.argv[1]))
  randr = random.randrange

  n = 5 * 10 ** 5
  p = 998244353
  ls = [0] * n
  for i in range(n):
    ls[i] = randr(0, p)
  print(n)
  print(*ls)


main()
