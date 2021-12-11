def main_case() -> None:
    n = int(input())  # [1, 15]
    ls = [int(x) for x in input().split()]  # [1, 16]

    # Factor out 2
    count = 0
    for i in range(n):
        while ls[i] % 2 == 0:
            ls[i] //= 2
            count += 1

    # Double largest number
    m = max(ls)
    res = sum(ls) - m + m * (2 ** count)
    print(res)


def main() -> None:
    t = int(input())  # [1, 10^4]
    for _ in range(t):
        main_case()


if __name__ == "__main__":
    main()


"""
python -m experiment.cf1609a.main < in.txt

%%%% begin
5
3
6 4 2
5
1 2 3 4 5
1
10
3
2 3 4
15
8 8 8 8 8 8 8 8 8 8 8 8 8 8 8
%%%%
50
46
10
26
35184372088846
%%%% end
"""
