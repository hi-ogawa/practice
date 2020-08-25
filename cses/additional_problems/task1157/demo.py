import sys

def main():
  n, m, = sys.argv[1:] or [32, 32]
  n, m = int(n), int(m)

  def mex(s):
    for i in range(len(s) + 1):
      if i not in s:
        return i

  def print2(data):
    for row in data:
      for x in row:
        print(f"{x:>4}", end='')
      print()

  rows = [set() for i in range(n)]
  cols = [set() for i in range(m)]
  data = [[0 for j in range(m)] for i in range(n)]

  for i in range(n):
    for j in range(m):
      x = mex(rows[i].union(cols[j]))
      rows[i].add(x)
      cols[j].add(x)
      data[i][j] = x

  print2(data)

main()
