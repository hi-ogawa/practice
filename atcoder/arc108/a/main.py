# CONTEST, AC

import math, sys

def main():
  s, p = list(map(int, sys.stdin.readline().strip().split()))

  # x^2 - s x + p = 0
  a = 1
  b = -s
  c = p

  q = b * b - 4 * a * c
  qr = math.isqrt(q)
  if qr * qr != q:
    print("No")
    return

  x2 = - b + qr
  y2 = - b - qr

  if x2 % 2 or y2 % 2 or y2 <= 0:
    print("No")
    return

  print("Yes")


main()
