#
# python misc/fibonacci.py 32
#


def fibonacci(n):
    x = 0
    y = 1
    print(f"0: 0")
    print(f"1: 1")
    for i in range(2, n):
        x, y = y, x + y
        print(f"{i}: {y}")


if __name__ == "__main__":
    import sys

    fibonacci(int(sys.argv[1]))
