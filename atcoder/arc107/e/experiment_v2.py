#
# Test 3^9 patterns and check if x = y
#   a b c d e
#   e
#   f
#   g     x
#   h       y
#

def solve(ls):
  mex = [
    [1, 2, 1],
    [2, 0, 0],
    [1, 0, 0]
  ]
  n = len(ls)
  for i in range(1, n):
    for j in range(1, n):
      ls[i][j] = mex[ls[i - 1][j]][ls[i][j - 1]]

  return ls[n - 2][n - 2] == ls[n - 1][n - 1]


def main():
  n = 5
  k = 2 * n

  # Generate 3^k patterns by 2^k x 2^k
  for m1 in range(1 << k):
    for m2 in range(1 << k):
      if m1 & m2 != m2:  # Check m2 ⊆ m1
        continue
      ls = [[0] * n for _ in range(n)]
      for i in range(n):
        if (m1 >> i) & 1:
          ls[0][i] += 1
        if (m2 >> i) & 1:
          ls[0][i] += 1
      for i in range(1, n):
        if (m1 >> (i + n)) & 1:
          ls[i][0] += 1
        if (m2 >> (i + n)) & 1:
          ls[i][0] += 1
      ok = solve(ls)
      if not ok:
        print(*ls, sep='\n')
        return


main()
