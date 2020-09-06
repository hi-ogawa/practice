def main():
  import sys, random
  random.seed(int(sys.argv[1]))
  randr = random.randrange

  n_lim = 1000000
  n = randr(1, n_lim + 1)
  s = ''
  for _ in range(n):
    s += chr(randr(ord('a'), ord('z') + 1))
  print(s)

main()
