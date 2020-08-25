import sys, random

def main():
  seed, = sys.argv[1:] or [0]
  random.seed(seed)

  n = random.randrange(3, 10)  # Num of vertices
  edges = []
  for v in range(1, n):  # Merge n-1 times
    u = random.randrange(0, v)
    edges.append([v, u])

  print(n)
  for [v, u] in edges:
    print(v + 1, u + 1)

main()
