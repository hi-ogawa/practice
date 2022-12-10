from sys import argv
import random


def main():
    random.seed(argv[-1])

    n0, n1, *_ = map(int, argv[1:])
    n = random.randrange(n0, n1)

    ls = [0] * n
    for i in range(n):
        ls[i] = random.randrange(1, n + 1)

    print(n)
    print(*ls)


main()
