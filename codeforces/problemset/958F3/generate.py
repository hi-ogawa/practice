def main():
  import sys, random
  random.seed(int(sys.argv[1]))
  randr = random.randrange

  n = 200000
  m = 45350
  k = 17840
  ls = [0] * n
  for i in range(n):
    ls[i] = randr(1, m + 1)

  print(n, m, k)
  print(*ls)


main()
