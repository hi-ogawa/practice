def main():
  import sys, random
  random.seed(int(sys.argv[1]))
  randr = random.randrange

  t = 1
  n = 8
  x = 20
  ls = [0] * n
  for i in range(n):
    ls[i] = randr(2, x + 1)
  print(t)
  print(n)
  print(*ls)


main()
