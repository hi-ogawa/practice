from sys import stdin


def main():
    """
    python hackerrank/projecteuler/102/format.py < hackerrank/projecteuler/102/p102_triangles.txt > hackerrank/projecteuler/102/p102_triangles_hackerrank.txt
    """
    lines = stdin.read().strip().split("\n")
    print(len(lines))
    for line in lines:
        print(line.replace(",", " "))


if __name__ == "__main__":
    main()
