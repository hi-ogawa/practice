#
# python misc/misc.py sqrt_continued_fraction 18181 1024
#


def mul_mm(m1, m2):
    a, b, c, d = m1
    aa, bb, cc, dd = m2
    return [a * aa + b * cc, a * bb + b * dd, c * aa + d * cc, c * bb + d * dd]


def mul_mv(m1, v2):
    a, b, c, d = m1
    aa, bb = v2
    return [a * aa + b * bb, c * aa + d * bb]


def sqrt_continued_fraction(n, k, debug=0):
    assert n > 0
    ls = [None] * k
    m = [1, 0, 0, 1]  # Accumulate convergents linear transform
    done = False
    for i in range(k):
        if debug:
            print(i, m)
        a = 1
        while True:
            a += 1
            x, y = mul_mv(m, [a, 1])
            x2, ny2 = x ** 2, n * (y ** 2)
            if debug >= 2:
                print(a, x, y, x2, ny2)
            if i % 2 == 0 and x2 > ny2:  # max{ a | [... ,a] <= sqrt(n)}
                break
            if i % 2 == 1 and x2 < ny2:  # min{ a | [... ,a] >= sqrt(n)}
                break
        a -= 1
        ls[i] = a
        m = mul_mm(m, [a, 1, 1, 0])
        if m[0] ** 2 == n * m[2] ** 2:
            break
    return ls


if __name__ == "__main__":
    import sys

    _, arg1, *args = sys.argv

    if arg1 == "sqrt_continued_fraction":
        arg2, arg3 = args
        print(sqrt_continued_fraction(int(arg2), int(arg3)))
