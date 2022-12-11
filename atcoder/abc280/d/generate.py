from sys import argv
import random


def main():
    random.seed(argv[-1])

    n0, n1, *_ = map(int, argv[1:])
    n = random.randrange(n0, n1)
    print(n)


main()
