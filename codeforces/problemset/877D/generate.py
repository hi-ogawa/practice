def main():
  n = m = k = 1000
  v0 = [1, 1]
  v1 = [n, m]
  print(n, m, k)
  for i in range(n):
    for j in range(m):
      print('.', end='')
    print()
  print(*v0, *v1)


main()
