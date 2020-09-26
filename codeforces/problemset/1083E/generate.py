def main():
  import argparse
  parser = argparse.ArgumentParser()
  parser.add_argument("n", type=int, default=10 ** 4)
  args = parser.parse_args()

  n = args.n
  print(n)
  for i in range(n):
    print(i + 1, n - i, 0)

main()
