def main():
  import sys, random
  random.seed(int(sys.argv[1]))
  randr = random.randrange

  n = 2 ** 17
  m = 2 ** 17
  p = 998244353
  ls1 = [0] * n
  ls2 = [9] * m
  for i in range(n):
    ls1[i] = randr(0, p)
  for i in range(m):
    ls2[i] = randr(0, p)
  print(n, m)
  print(*ls1)
  print(*ls2)

main()
