#
# python misc/misc.py sqrt_continued_fraction 2 32
# python misc/misc.py sqrt_digits 2 1000
# python misc/misc.py rational_to_digits 1 7 32
# python misc/misc.py solve_root 2 10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000 1 # noqa
# python misc/misc.py sqrt_continued_fraction_periodic 18181 1
# python misc/misc.py solve_pell 18181
# python misc/misc.py experiment_generalized_continued_fraction 20
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


# [ Brute force ]
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


# Based on Mobius transform fixed point (cf. Marius Beceanu)
def sqrt_continued_fraction_periodic(N, debug=0):
    #
    # CF recurrence is defined by
    #   x = √N > 0
    #   x_0 = x
    #   a_k = ⌊x_k⌋ > 0
    #   x_k+1 = 1 / (x_k - a_k) = 1 / {x_k} > 1
    #
    # Then, we can write (NOTE: the matrix indicates Mobius transform)
    #   x = | a_0  1 | ... | a_k-1  1 |  = | e' e | x_k  (NOTE: e'/d' and e/d is convergents)
    #       | 1    0 |     | 1      0 |    | d' d |
    #
    # By inverting, we have
    #   x_k = |  d   -e  |^{-1} x
    #         | -d'  e' |
    #       = ... (magical transform due to x^2 = N) ...
    #       = | 1   μ_k | x  (for some μ_k, λ_k > 0 (proved so))
    #         | 0   λ_k |
    #       = (x + μ_k) / λ_k
    #
    # Looking for recurrence of μ_k, η_k,
    #   x_k+1 = | 0    1 | x_k = | 0    1 | | 1   μ_k | x
    #           | 1 -a_k |       | 1 -a_k | | 0   λ_k |
    #         = ... (Again magical transform ) ...
    #         = | 1   a_k.λ_k - η_k                | x
    #           | 0  (N - (a_k.λ_k - η_k)^2) / λ_k |
    # So,
    #   η_k+1 = a_k.λ_k - η_k
    #   λ_k+1 = (N - η_k+1^2) / λ_k
    #   a_k+1 = ⌊x_k+1⌋ = ⌊(⌊x⌋ + μ_k+1) / λ_k+1⌋ = (a_0 + μ_k+1) // λ_k+1 (∵ λ_k > 0)
    #
    # Here μ_k and λ_k are bounded (proved so), so by pigeonhole principle, same pair
    # are bound to appear, which gives periodic CF.
    #
    # Going further, we can prove remarkable fact that, by defining
    #   y_k = |0 1| | 1  - μ_k | x = λ_k / (x - μ_k)
    #         |1 0| |      λ_k |
    # We have,
    #   y_1 = y_p+1 = [a_p, a_p-1, ..., a_2, a_1] : periodic CF
    #   x_1 = x_p+1 = [a_1, a_2, ... a_p-1, a_p] : periodic CF
    #   a_p = 2 a_0
    #   y_p = x_1  ==>  [a_p-1, .., a_1, a_p] = [a_1, a_2, ... a_p-1, a_p] (i.e. symmetric each other)
    #

    # Initialize (a0, eta0, lam0)
    a0 = solve_root(2, N)  # max {a | a^2 < N}
    if a0 ** 2 == N:
        raise RuntimeError(
            f"[sqrt_continued_fraction_periodic] Not square free N = {N} = {a0}^2"
        )
    a = a0
    eta = 0
    lam = 1
    result = [a]

    # To identify period, we hold eta1 and lam1
    eta = a * lam - eta
    lam = (N - eta ** 2) // lam
    a = (a0 + eta) // lam
    result += [a]
    eta1, lam1 = eta, lam
    if debug:
        print("a0:", a0, "eta1:", eta1, "lam1:", lam1)

    # Iterate until (eta, lam) = (eta1, lam1) (NOTE: proved bound ⌊x⌋.(⌊x⌋ + 1))
    for i in range(a0 * (a0 + 1)):
        eta = a * lam - eta
        lam = (N - eta ** 2) // lam
        a = (a0 + eta) // lam
        if eta == eta1 and lam == lam1:
            break
        result += [a]
    else:
        raise RuntimeError(
            f"[sqrt_continued_fraction_periodic] Bug in theory? or code?"
        )

    if debug:
        print("period:", len(result) - 1)

    return result


def solve_pell(n, debug=0):
    #
    # From analysis in `sqrt_continued_fraction_periodic`, we have
    #   x = | a0 1 | x1 = A0 x1
    #       | 1  0 |
    #   x1 = | a1 1 | .. | ap 1 | x1 = (A1..Ap) x1
    #        | 1  0 |    | 1  0 |
    #   x = A0 (A1..Ap) A0^-1 x
    #
    # Here by construction, we have
    #   det(A0 (A1..Ap) A0^-1) = (-1)^p
    #
    # Also, from symmetric property and ap = 2a0, we have
    #   S = A1..Ap-1 : symmetric
    #   A0 (A1..Ap) A0^-1
    #     = A0 S Ap A0^-1
    #     = | a0 1 | S | 2a0 1 | |     1 |
    #       | 1  0 |   | 1   0 | | 1 -a0 |
    #     = | a0 1 | S | 1 a0 |
    #       | 1  0 |   |   1  |
    #     = | u  t |  (for some u, v, t where diagonal coincides due to S symmetric)
    #       | v  u |
    #
    # Here noting that,
    #   x =  | u  t | x
    #        | v  u |
    #   <=> x (v x + u) = (u x + t)
    #   <=> v x^2 = t
    #
    # then, we finally obtain,
    #   x = | p  Nq | x
    #       | q  p  |
    #   and
    #   (-1)^p = det | p  Nq | = p^2 - N q^2  (Pell's equation (negative if odd periodic))
    #                | q  p  |
    #
    # From negative solution, positive one is easy to construct by Chakravala self multiplication.
    #
    # TODO: Prove "Pell equation => Periodic CF" with minimality, positive/negative etc...
    #
    a0, *aps = sqrt_continued_fraction_periodic(n, debug=debug)
    A0 = [a0, 1, 1, 0]
    A0_inv = [0, 1, 1, -a0]
    A = A0
    for a in aps:
        A = mul_mm(A, [a, 1, 1, 0])
    A = mul_mm(A, A0_inv)
    if debug:
        print("A:", A)
    u, v = A[0], A[2]
    k = -1 if len(aps) % 2 else 1
    assert A[0] == A[3]
    assert A[1] == A[2] * n
    assert A[0] ** 2 - n * A[2] ** 2 == k
    return u, v, k


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


def reduce_common_factors(n0, m0):
    n, m = abs(n0), abs(m0)
    n, m = [max(n, m), min(n, m)]
    while m != 0:
        n, m = m, n % m
    return n0 // n, m0 // n


class QQ:
    def __init__(self, p, q=1):
        self.p, self.q = p, q

    def __repr__(x):
        return f"QQ({x.p}/{x.q})"

    def __add__(x, y):
        p = x.p * y.q + x.q * y.p
        q = x.q * y.q
        p, q = reduce_common_factors(p, q)
        return QQ(p, q)

    def __mul__(x, y):
        p = x.p * y.p
        q = x.q * y.q
        p, q = reduce_common_factors(p, q)
        return QQ(p, q)

    def __truediv__(x, y):
        p = x.p * y.q
        q = x.q * y.p
        p, q = reduce_common_factors(p, q)
        return QQ(p, q)


def experiment_generalized_continued_fraction(k, debug=0):
    #
    # From Euler's product identity,
    #   e^z = [0, {1, 1}, {-z/1, z/1 + 1}, {-z/2, z/2 + 1}, ...]
    #
    # Thus
    #   e^-z = [0, {1, 1}, {z/1, (1-z)/1}, {z/2, (2-z)/2}, ...]
    #   1/e = [0, {1, 1}, {1/1, 0}, {1/2, 1/2}, {1/3, 2/3}, {1/4, 3/4}, ...]
    #   e = [1, {1, 0}, {1/2, 1/2}, {1/3, 2/3}, {1/4, 3/4}, ..]
    #   1/(e-1) = [0, {1/2, 1/2}, {1/3, 2/3}, {1/4, 3/4}, ...]
    #
    # The famous Euler's formula (which I cannot prove yet) is this
    #   e = [2,  1, 2, 1,  1, 4, 1,  1, 6, 1, ..., 1, 2n, 1, ...]
    #   1/(e-1) = [0,  1, 1, 2,  1, 1, 4,  1, 1, 6, ..., 1, 1, 2n, ...]
    #

    # Accumulate mobius transform (aka. convergents)
    m = [QQ(1), QQ(0), QQ(0), QQ(1)]

    for n in range(1, k):
        # Each step is Mobius transform
        #   x_n = a_n + b_n+1 / x_n+1 = | a_n  b_n+1 | x_n+1
        #                               | 1          |
        a = QQ(n - 1, n)
        b = QQ(1, n + 1)
        m = mul_mm(m, [a, b, QQ(1), QQ(0)])

    x = m[0] / m[2]  # 1 / (e - 1)
    y = QQ(1) / x + QQ(1)  # e
    return y.p / y.q, y


# Newton's divided difference
def poly_interpolation(ls, debug=0):
    #
    # Given n points [(x1, y1), (x2, y2), .., (xn, yn)], we find polynomials { p[i,j] | i, j },
    # where "j-i"-degree poly p[i, j] interpolates "j-i+1" points [(xi, yi), .., (xj, yj)].
    #
    # From the uniqueness property of interpolation polynomial, we have a, b s.t.
    #   p[i, j+1] = p[i, j] + a.(x-xi)..(x-xj)
    #   p[i, j+1] = p[i+1, j+1] + b.(x-x_i+1)..(x-x_j+1)
    # Here, comparing the coefficient of largest monimial x^p, we actually find that a = b,
    # and thus, we write a = b = c[i, j+1].
    #
    # Then, we can find remarkable recursive relation (aka. divided difference)
    # for { c[i, j] | i, j } as follows,
    #   c[i, i] = yi
    #   c[i, j] = (c[i+1, j] - c[i, j-1]) / (x_j - x_i)
    #

    n = len(ls)
    c = [[0 for _ in range(n)] for _ in range(n)]

    # Base case
    for i in range(n):
        c[0][i] = ls[i][1]

    # Recursive case
    for i in range(1, n):
        for j in range(n - i):
            dc = c[i - 1][j + 1] - c[i - 1][j]
            dx = ls[j + i][0] - ls[j][0]
            c[i][j] = dc / dx

    return c


def test_poly_interpolation():
    x1, x2, x3, x4 = 1, 2, 3, 4
    y1, y2, y3, y4 = 1, -1, 1, -1
    ls = [[x1, y1], [x2, y2], [x3, y3], [x4, y4]]
    c = poly_interpolation(ls)
    c1, c2, c3, c4 = c[0][0], c[1][0], c[2][0], c[3][0]

    def f(x):
        # Horner scheme
        return c1 + (x - x1) * (c2 + (x - x2) * (c3 + (x - x3) * c4))

    print("c:", c)
    print("f(x):", f(x1), f(x2), f(x3), f(x4))

    import math

    for x, y in ls:
        assert math.isclose(f(x), y)


if __name__ == "__main__":
    import sys

    _, func_name, *args = sys.argv
    args = map(int, args)
    result = locals()[func_name](*args)
    if result is not None:
        print(result)
