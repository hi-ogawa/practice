def main():
  import sys, random
  random.seed(int(sys.argv[1]))
  randr = random.randrange

  n = randr(1, 11)
  ls1 = [0] * n
  ls2 = [0] * n
  for i in range(n):
    ls1[i] = randr(1, n + 1)
    ls2[i] = randr(1, n + 1)

  ls1.sort()
  ls2.sort()
  print(n)
  print(*ls1)
  print(*ls2)


main()
