from sys import argv
from random import seed, randrange, choices

def main():
    seed(argv[-1])

    n0, n1, m0, m1, *_ = map(int, argv[1:])
    assert n0 >= 2

    n = randrange(n0, n1 + 1)
    m = randrange(m0, m1 + 1)
    k = randrange(0, n + 1)

    print(n, m, k)

    for _ in range(m):
      u, v = choices(range(1, n + 1), k=2)
      a = randrange(0, 2)
      print(u, v, a)

    s = choices(range(1, n + 1), k=k)
    print(*s)


main()
