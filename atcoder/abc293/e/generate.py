from sys import argv
import random


def main():
    random.seed(argv[-1])

    n, *_ = map(int, argv[1:])
    a = random.randrange(1, n)
    x = random.randrange(1, n)
    m = random.randrange(1, n)
    print(a, x, m)


main()
