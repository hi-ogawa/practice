
def main():
  import sys, random
  random.seed(int(sys.argv[1]))
  randr = random.randrange

  mex = [
    [1, 2, 1],
    [2, 0, 0],
    [0, 0, 0]
  ]
  n = 50
  ls = [[0] * n for _ in range(n)]
  for i in range(n):
    ls[i][0] = randr(0, 3)
    ls[0][i] = randr(0, 3)

  for i in range(1, n):
    for j in range(1, n):
      x = ls[i - 1][j]
      y = ls[i][j - 1]
      ls[i][j] = mex[x][y]

  for i in range(n):
    cnts = [0] * 3
    for j in range(n):
      x = ls[i][j]
      cnts[x] += 1
      print(x, end=' ')
    print(cnts)


main()
