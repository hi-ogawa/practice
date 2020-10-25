def main():
  import sys, random
  random.seed(int(sys.argv[1]))
  randr = random.randrange

  n = 5 * 10 ** 5
  ls = [1] * n
  # for i in range(n):
    # ls[i] = randr(0, 2)

  print(n)
  print(*ls, sep='')


main()
