def main():
  import sys, random
  random.seed(int(sys.argv[1]))
  randr = random.randrange

  n = 2 * 10 ** 5
  ls = [0] * n
  for i in range(n):
    ls[i] = randr(- 10 ** 4, 10 ** 4)

  print(n)
  print(*ls)


main()
