#
# python misc/misc.py sqrt_continued_fraction 2 32
# python misc/misc.py sqrt_digits 2 1000
# python misc/misc.py rational_to_digits 1 7 32
# python misc/misc.py solve_root 2 10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000 1 # noqa
#

#
# CLAIM.
#   For continued fraction [a0; a1, a2, ..],
#   we have convergents E(0,k)/D(0,k) as linear recurrence
#
#     E(k,k) = ak
#     D(k,k) = 1
#
#     |E(i,k)| = | ai 1 | |E(i+1,k)|
#     |D(i,k)|   | 1  0 | |D(i+1,k)|
#
#   Therefore,
#
#     |E(0,k)| = | a0 1 | | a1 1 | .. | ak 1 | |1|
#     |D(0,k)|   | 1  0 | | 1  0 | .. | 1  0 | |0|
#
#
# PROP.
#   Writing E(k) = E(0, k) and D(0, k), we have
#
#     | a0 1 | | a1 1 | .. | ak 1 | = | E(k) E(k-1) |
#     | 1  0 | | 1  0 | .. | 1  0 |   | D(k) D(k-1) |
#
#   Also, this is equivalent to,
#
#     E(k) = ak E(k-1) + E(k-2)
#     D(k) = ak D(k-1) + D(k-2)
#
#   PROOF. It follows from the recurrence relation in CLAIM.
#
#
# PROP.
#    E(k) D(k-1) - E(k-1) D(k) =  det | E(k) E(k-1) | = (-1)^k
#                                     | D(k) D(k-1) |
#
#    Also, from Bezout's identity, gcd(E(k), D(k)) = 1.
#
#   PROOF.
#     It follows from det | ai 1 | = 1
#                         | 1  0 |
#
#
# PROP.
#     E(2k)    E(2k+2)                        E(2k+1)
#     ----- <= ------- <= [a0; a1, a2, ..] <= -------
#     D(2k)    D(2k+2)                        D(2k+1)
#
#   PROOF.
#     These inequality follows by construction of the continued fraction.
#
#
# PROP.
#    E(k+1)     E(k)      (-1)^k
#    ------  -  ----  =  ----------
#    D(k+1)     D(k)     D(k)D(k+1)
#
#   PROOF. It follows from above PROP.
#


def mul_mm(m1, m2):
    a, b, c, d = m1
    aa, bb, cc, dd = m2
    return [a * aa + b * cc, a * bb + b * dd, c * aa + d * cc, c * bb + d * dd]


def mul_mv(m1, v2):
    a, b, c, d = m1
    aa, bb = v2
    return [a * aa + b * bb, c * aa + d * bb]


def sqrt_continued_fraction_generator(n, debug=0):
    import itertools

    m = [1, 0, 0, 1]  # Accumulate convergents linear transform
    for i in itertools.count():
        if debug:
            print(i, m)
        #
        # TODO:
        #   Accelerate by some sort of optimization for
        #     max{ a | (a e' + e)^2 <= (a d' + d)^2 n } if 2 | i
        #     min{ a | (a e' + e)^2 >= (a d' + d)^2 n } if 2 † i
        #
        #     e.g. based on some quadratic equation solver
        #       (a e' + e)^2 <= (a d' + d)^2 n
        #         <=> (n d'^2 - e^2) a^2
        #             + 2 (n d' d - e' e) a + (n d^2 - e^2) >= 0
        #
        #  For now, brute force by a = 0, 1, ...
        #
        a = 1
        while True:
            a += 1
            x, y = mul_mv(m, [a, 1])  # = (a e' + e) / (a d' + d)
            x2, ny2 = x ** 2, n * (y ** 2)
            if debug >= 2:
                print(a, x, y, x2, ny2)
            if i % 2 == 0 and x2 > ny2:  # max{ a | [... ,a] <= sqrt(n)}
                break
            if i % 2 == 1 and x2 < ny2:  # min{ a | [... ,a] >= sqrt(n)}
                break
        a -= 1
        m = mul_mm(m, [a, 1, 1, 0])
        yield a, m[0], m[2]
        if m[0] ** 2 == n * m[2] ** 2:
            break


def sqrt_continued_fraction(n, k, debug=0):
    import itertools

    gen = sqrt_continued_fraction_generator(n, debug=debug)
    for i, (a, e, d) in enumerate(itertools.islice(gen, k)):
        print(f"{i}: {a} ({e} / {d})")


def rational_to_digits_generator(p, q, b=10, debug=0):
    # p / q in base b

    #
    # In general, for x ∈ [0, 1), we can obtain b-digits by:
    #   d0 = 0,       x0 = x
    #   d1 = ⌊b.x0⌋,  x1 = {b.x0} ∈ [0, 1)
    #   d2 = ⌊b.x1⌋,  x2 = {b.x1} ∈ [0, 1)
    #   ...
    #
    # For rational case x = p/q, this translates to
    #   d0 = 0           x0 = p/q = p0/q
    #   d1 = b.p0 // q,  x1 = (b.p0 % q) / q = p1/q
    #   d2 = b.p1 // q,  x2 = (b.p1 % q) / q = p2/q
    #   ...
    # So, we can only keep (p_i)_i, which is what the loop below does.
    #
    # PROP.
    #   If b, p ∈ Zq* (units of cyclic group i.e. gcd(b, p) = gcd(p, q) = 1),
    #   then digits repeats since {p, bp, bbp, ...} = p<b> ⊆ Zq.
    #   Especially when p = 1, it becomes <b>.
    #   So, repeat period is at most |<b>| <= |Zq*| = Φ(q).
    #
    # NOTE
    #   1. If gcd(b, q) ≠ 1 (i.e b ∉ Zq*), then we can reduce bp/q = p'/q'
    #      and we can do the same discussion as above.
    #      TODO: not really... need to consider gcd(b^k, q). (e.g. 10/4 ~> 2/4 = 1/2 ~> 10/2)
    #   2. Digits repeatance might not be necessary equivalent to repeatance of <b> ??
    #      Just "by a chane", haviding b p // q = b p' // q even if p != p' ??
    #      TODO: find such counter example
    #
    d0, p = divmod(p, q)
    yield d0  # TODO: This assumes b=10
    if debug:
        p0 = p
        print(d0, p0, "@")
    while True:
        d, p = divmod(p * b, q)
        if debug:
            print(d, p, "@" if p == p0 else "")
        yield d


def experiment_rational_to_digits(p, q, k, b=10):
    gen = rational_to_digits_generator(p, q, b=b, debug=1)
    for i in range(k):
        next(gen)


def rational_to_digits(p, q, k, b=10, debug=0):
    import itertools

    gen = rational_to_digits_generator(p, q, b=b, debug=debug)
    print(f"{next(gen)}.", end="", flush=True)
    for d in itertools.islice(gen, k):
        print(d, end="", flush=True)
    print()


def sqrt_digits_generator(n, b=10, debug=0):
    import itertools

    gen_convergents = sqrt_continued_fraction_generator(n, debug=debug)

    #
    # States
    #   e/d: last convergents
    #   k: last known digit position
    #   gen_digits: last digit generator
    #

    # Initialize state
    _, ee, dd = next(gen_convergents)
    kk = 0
    ggen_digits = rational_to_digits_generator(ee, dd, b, debug=debug)
    yield next(ggen_digits)  # Pop integral part

    for i, (_, e, d) in enumerate(gen_convergents):
        # By multipling "b ** kk", we fast-skip first "kk" digits
        # since we know "ee/dd" ~ "e/d".
        e *= b ** kk
        gen_digits = rational_to_digits_generator(e, d, b, debug=debug)
        next(gen_digits)  # Pop integral part
        for k, x in enumerate(gen_digits):
            xx = next(ggen_digits)
            if xx == x:
                # Output coinciding digit
                yield x
                continue

            # Found conflicting digit
            kk += k
            ggen_digits = itertools.chain([x], gen_digits)  # Fake "x" was look-ahead
            break


def sqrt_digits(n, k, b=10, debug=0):
    import itertools

    gen = sqrt_digits_generator(n, b=b, debug=debug)
    print(f"{next(gen)}.", end="", flush=True)
    for d in itertools.islice(gen, k):
        print(d, end="", flush=True)
    print()


def solve_root(p, b, debug=0):
    # max { a \in \ZZ | a^p <= b }

    # [ Brute force ]
    # a = 1
    # while True:
    #     ap = a ** p
    #     if ap == b:
    #         return a
    #     if ap > b:
    #         return a - 1
    #     a += 1
    # return a

    # [ Newton-Raphson ]
    # f(a) = a^p - b
    # g(a) = a - f(a)/f'(a) = ((p-1) a^p + b) / p a^{p-1}
    pp = p - 1
    a = (pp + b) // p
    a = 1  # Initially f(1) <= 0
    while True:
        a = (pp * a ** p + b) // (p * a ** pp)  # Approach to the root from right # noqa
        if debug:
            print("[solve_root]", a)
        if a ** p <= b:  # a \in (<root> - 1, <root>] due to "division rounding" # noqa
            break
    return a


if __name__ == "__main__":
    import sys

    _, func_name, *args = sys.argv
    args = map(int, args)
    result = locals()[func_name](*args)
    if result is not None:
        print(result)
