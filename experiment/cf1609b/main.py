# AC

import os
from sys import stderr, stdin, stdout

DEBUG = os.getenv("DEBUG")
PATTERN = bytearray("abc", "ascii")


def main_case() -> None:
    n, q = map(int, stdin.readline().split())  # [1, 10^5]
    s = bytearray(input(), "ascii")

    # Count initial state
    count = 0
    for i in range(n - 2):
        if s[i : i + 3] == PATTERN:
            count += 1

    # Process queries
    for _ in range(q):
        i_, c = stdin.readline().split()
        i = int(i_) - 1

        # Check three ranges where possibly "abc" appeared or disappeared
        #   ? ? X ? ?
        #   <--->
        #     <--->
        #       <--->
        for j in range(i - 2, i + 1):
            if s[j : j + 3] == PATTERN:
                count -= 1

        s[i] = ord(c)
        if DEBUG:
            print(s, file=stderr)
            print(count, file=stderr)

        for j in range(i - 2, i + 1):
            if s[j : j + 3] == PATTERN:
                count += 1

        stdout.write(f"{count}\n")


def main() -> None:
    main_case()


if __name__ == "__main__":
    main()


"""
python -m experiment.cf1609b.main < experiment/cf1609b/in.txt

%%%% begin
9 10
abcabcabc
1 a
1 b
2 c
3 a
4 b
5 c
8 a
9 b
1 c
4 a
%%%%
3
2
2
2
1
2
1
1
1
0
%%%% end
"""
