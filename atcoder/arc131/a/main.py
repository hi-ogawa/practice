# AC

from sys import stdin
import os

dbg = os.getenv("DEBUG")


def main_case() -> None:
    # [1, 10^8]
    a = int(stdin.readline())
    b = int(stdin.readline())

    #      <- 8 ->     <- 9 ->
    #  x = [  a  ] [0] [  y  ]
    #  y = ([  b  ] [0]) / 2

    print(a * (10 ** 10) + (5 * b))


def main() -> None:
    main_case()


if __name__ == "__main__":
    main()

"""
python misc/run.py atcoder/arc131a/main.py

%%%% begin
13
62
%%%%
130000000310
%%%% end


%%%% begin
69120
824
%%%%
691200000004120
%%%% end
"""
