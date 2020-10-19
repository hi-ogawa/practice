def main():
  import sys, random
  random.seed(int(sys.argv[1]))
  randr = random.randrange

  x_lim = 10 ** 9
  n = 50
  ls = [0] * n
  for i in range(n):
    ls[i] = randr(-x_lim, x_lim + 1)

  mean = sum(ls) // n
  for i in range(n):
    ls[i] -= mean
  ls[0] -= sum(ls)

  print(n)
  print(*ls)

main()
