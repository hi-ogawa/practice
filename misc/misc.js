const gcd = (n, m) => { // eslint-disable-line
  const {abs, max, min} = Math;
  n = abs(n);
  m = abs(m);
  [n, m] = [max(n, m), min(n, m)];
  if (m === 0) {
    throw new Error('[gcd]');
  }
  for (;;) {
    const r = n % m;
    if (r === 0) {
      return m;
    }
    [n, m] = [m, r];
  }
};
