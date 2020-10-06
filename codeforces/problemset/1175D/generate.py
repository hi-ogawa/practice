def main():
  import sys, random
  random.seed(int(sys.argv[1]))
  randr = random.randrange

  n = randr(5, 8)
  k = randr(2, n + 1)
  ls = [0] * n
  for i in range(n):
    ls[i] = randr(-10, 11)

  print(n, k)
  print(*ls)


main()
