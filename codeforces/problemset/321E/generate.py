def main():
  import sys, random
  random.seed(int(sys.argv[1]))
  randr = random.randrange

  n = 4000
  m = 800
  ls = [[0] * n for _ in range(n) ]
  for i in range(n):
    for j in range(i + 1, n):
      ls[i][j] = ls[j][i] = randr(0, 10)

  s = ''
  s += f"{n} {m}\n"
  for i in range(n):
    for j in range(n):
      if j: s += ' '
      s += str(ls[i][j])
    s += '\n'
  print(s.strip())


main()
