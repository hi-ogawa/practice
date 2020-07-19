//
// node misc/radical.js 1000
//

// We enumerate prime factors during sieve construction (cf. `makeTotient` from totient.js)
const makeRadical = (n) => {
  const a = new Uint8Array(n); // sieve
  const b = new Uint32Array(n); // b[k] = ∏_{p | k} p
  a.fill(1);
  b.fill(1);

  // 0, 1: not prime
  a[0] = 0;
  a[1] = 0;

  // 2: prime
  for (let i = 4; i < n; i += 2) {
    a[i] = 0;
    b[i] *= 2;
  }

  // Sieve loop
  for (let i = 3; i <= n / 2; i += 2) { // Check up to n / 2 (instead of usual sqrt(n))
    // i: not prime
    if (a[i] === 0) {
      continue;
    }

    // i: prime
    let ie = 2 * i; // Cross out from 2 * i (instead of usual i^2)
    while (ie < n) {
      a[ie] = 0;
      b[ie] *= i;
      ie += i;
    }
  }

  // Set b[p] = p
  for (let i = 2; i < n; i++) {
    if (a[i] === 1) {
      b[i] = i;
    }
  }

  return b;
};

const main = (n) => {
  const ls = makeRadical(n);
  for (let i = 0; i < ls.length; i++) {
    console.log(`${i}: ${ls[i]}`);
  }
};

main(...process.argv.slice(2));
