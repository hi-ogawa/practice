from sys import argv
import random

def main():
  random.seed(argv[-1])
  randr = random.randrange

  n0, n1, nq0, nq1, *_ = map(int, argv[1:])
  n = randr(n0, n1)
  nq = randr(nq0, nq1)

  ls = [0] * n
  for i in range(n):
    ls[i] = 10 ** i

  edges = [0] * (n - 1)
  for i in range(n - 1):
    edges[i] = [i + 1, randr(0, i + 1)]

  adj = [[0] * n for _ in range(n)]
  for x, y in edges:
    adj[x][y] = adj[y][x] = 1

  init_edges = list(edges)

  def get_reachables(r):
    q = [(r, -1)]
    res = [r]
    while len(q):
      x, xp = q.pop(0)
      for y in range(n):
        if y == xp or not adj[x][y]:
          continue
        q.append((y, x))
        res.append(y)
    return res

  qs = [0] * nq
  for i in range(nq):
    # Only cut/link
    t = 0
    x, y = random.choice(edges)
    edges.remove([x, y])
    adj[x][y] = adj[y][x] = 0
    z = random.choice(get_reachables(x))
    w = random.choice(get_reachables(y))
    edges.append([z, w])
    adj[z][w] = adj[z][w] = 1
    qs[i] = [t, x, y, z, w]

  print(n, nq)
  print(*ls)

  for x in init_edges:
    print(*x)

  for x in qs:
    print(*x)


main()
