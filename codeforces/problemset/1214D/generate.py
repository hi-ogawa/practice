def main():
  import sys
  n = int(sys.argv[1])
  m = n
  print(n, m)
  for i in range(n):
    print('.' * m)


main()
