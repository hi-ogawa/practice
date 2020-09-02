# AC

# NOTE: Same as main.cpp, but with python's big integer...


from sys import stdin


def gcd(x, y):
  if x < y:
    x, y = y, x
  while y > 0:
    x, y = y, x % y
  return x


def bezout(x, y):
  if x < y:
    x, y = y, x
  c1, c2 = x, y
  a1, a2 = 1, 0
  b1, b2 = 0, 1
  while c2 > 0:
    q, r = c1 // c2, c1 % c2;
    a1, a2 = a2, a1 - q * a2
    b1, b2 = b2, b1 - q * b2
    c1, c2 = c2, r
  return a1, b1


def main():
  n, p, w, d = list(map(int, stdin.readline().strip().split()))

  g = gcd(w, d)
  if p % g > 0:
    print(-1); return

  # WLOG, gcd(w, d) = 1
  w //= g
  d //= g
  p //= g
  a, b = bezout(w, d)

  # Find min y >= 0  s.t. x w + y d = p
  x = p * a
  y = p * b
  if y < 0:
    s = (-y + w - 1) // w
    x -= s * d
    y += s * w
  if y > 0:
    s = y // w
    x += s * d
    y -= s * w

  if x < 0 or x + y > n:
    print(-1); return

  z = n - (x + y)
  print(x, y, z)


if __name__ == "__main__":
  main()


"""
python codeforces/problemset/1244C/main.py
"""
