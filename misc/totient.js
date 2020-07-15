//
// node misc/totient.js 1000000
//

// Euler's totient based on prime sieves
//   ϕ(n) = n . ∏ (p - 1) / p
const makeTotient = (n) => {
  const a = new Uint8Array(n); // sieve
  const b = new Uint32Array(n); // n . ∏ (p - 1) / p
  a.fill(1);
  b.fill(1);

  // Initialize b[i] = i (later we accumulate prime factors by (b[i] / p) * (p - 1))
  for (let i = 0; i < n; i++) {
    b[i] = i;
  }

  // 0, 1: not prime
  a[0] = 0;
  a[1] = 0;

  // 2: prime
  for (let i = 4; i < n; i += 2) {
    a[i] = 0;
    b[i] /= 2;
  }

  // Sieve loop
  const ndiv2 = Math.floor(n / 2);
  for (let i = 3; i <= ndiv2; i += 2) { // Check up to n / 2 (instead of usual sqrt(n))
    // i: not prime
    if (a[i] === 0) {
      continue;
    }

    // i: prime
    let ie = 2 * i; // Cross out from 2 * i (instead of usual i^2)
    while (ie < n) {
      a[ie] = 0;
      b[ie] = (b[ie] / i) * (i - 1); // Divide first to keep it integer
      ie += i;
    }
  }

  // Set ϕ(p) = p - 1
  for (let i = 2; i < n; i++) {
    if (a[i] === 1) {
      b[i] = i - 1;
    }
  }

  return b;
};

const main = (n) => {
  const totient = makeTotient(n);
  for (let i = 0; i < totient.length; i++) {
    console.log(`${i}: ${totient[i]}`);
  }
};

main(...process.argv.slice(2));
