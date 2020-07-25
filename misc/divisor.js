//
// node misc/divisor.js 1000000
//

// σ_x(n) = \sum_{d | n} d^x
// TODO: support x = 0
const makeDivisor = (n, x) => {
  const {log, floor} = Math;

  const a = new Uint8Array(n); // sieve
  const b = new Uint32Array(n); // σ_x(n)
  a.fill(1);
  b.fill(1);

  // 0, 1: not prime
  a[0] = 0;
  a[1] = 1;
  b[0] = 0;

  // Sieve loop
  for (let p = 2; p <= floor(n / 2); p++) { // Check up to n / 2 (instead of usual sqrt(n))
    // p: not prime
    if (a[p] === 0) {
      continue;
    }

    // p: prime

    // Cross out multiples as usual
    {
      for (let pm = p ** 2; pm < n; pm += p) {
        a[pm] = 0;
      }
    }

    // Cumulatively multiply since σ_x is multiplicative
    for (let e = 1; e <= floor(log(n) / log(p)); e++) {
      // Sweep through n with ν_p(n) = e

      // Multiplicativity base case
      // σ_x(p^e) = 1 + p^x + p^2x + ... + p^ex = (p^{(e+1) x} - 1) / (p^x - 1)
      const sigma = (p ** ((e + 1) * x) - 1) / (p ** x - 1);

      const pe = p ** e;
      for (let pm = pe, i = 1; pm < n; pm += pe, i++) {
        // Skip ν_p(n) > e
        if (i % p == 0) {
          continue;
        }
        b[pm] *= sigma;
      }
    }
  }

  // Set σ_x(p) = 1 + p^x for prime p > n / 2
  for (let p = floor(n / 2); p < n; p++) {
    if (a[p] === 1) {
      b[p] = 1 + p ** x;
    }
  }

  return b;
};

const main = (n = 1000, x = 1) => {
  const divisor = makeDivisor(n, x);
  for (let i = 0; i < divisor.length; i++) {
    const sigma = divisor[i];
    const mark = ['+', '0', '-'][Math.sign(sigma - 2 * i) + 1];
    console.log(`${i}: ${sigma} (${mark})`);
  }
};

main(...process.argv.slice(2).map(Number));
