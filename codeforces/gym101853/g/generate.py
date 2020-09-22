def main():
  import sys, random, math
  random.seed(int(sys.argv[1]))
  randr = random.randrange

  t = 10
  m_lim = 1000000
  ls = []
  while len(ls) < t:
    m = randr(1, m_lim + 1)
    a = randr(0, m)
    b = randr(0, m)
    g = math.gcd(a, m)
    if b % g == 0:
      ls.append([a, b, m])

  print(t)
  for x in ls:
    print(*x)

main()
