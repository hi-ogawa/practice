# WIP

import os
from sys import stdin
from typing import Callable, List

dbg = bool(os.getenv("DEBUG"))
read_tokens: Callable[[], List[str]] = lambda: stdin.readline().split()


def main_case() -> None:
    pass


def main() -> None:
    main_case()
    # t, = map(int, read_tokens())
    # for _ in range(t):
    #     main_case()


if __name__ == "__main__":
    main()

"""
python {{RUNPY}} {{FILE}}
make black isort mypy SRC={{FILE}}

{{TESTS}}
"""
