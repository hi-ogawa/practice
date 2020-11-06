
# Example to test performance

def main():
  n = 4 * 10 ** 5
  nq = 4 * 10 ** 5
  ls = [0] * n
  edges = [0] * (n - 1)
  qs = [0] * nq

  for i in range(n):
    ls[i] = 1

  for i in range(n - 1):
    edges[i] = [1, i + 2]

  for i in range(nq):
    if i % 2:
      qs[i] = [1, 1, 1]
    else:
      qs[i] = [2, 1]

  print(n, nq)
  print(*ls)
  for xy in edges:
    print(*xy)
  for q in qs:
    print(*q)


main()
