//
// node misc/factorize.js 123456789
//

const factorize = (n) => {
  let q = n;
  const factors = [];
  let i = 2;
  while (true) { // eslint-disable-line
    // q < i^2  =>  (q/i) | q   =>  (contradiction)
    // i | q        (q/i) < i
    if ((i * i) > q) {
      break;
    }

    // Noting
    //   j < i                   =>  j !| i (not divisible)
    //   j !| q  (not divisble)
    //   i  | q  (divisible)
    // Thus, we have
    //   i: prime
    if (q % i === 0) {
      let e = 0;
      while (q % i === 0) {
        q /= i;
        e += 1;
      }
      factors.push([i, e]);
    }
    i++;
  }

  // q | n
  if (q > 1) {
    factors.push([q, 1]);
  }

  return factors;
};

// cf. factorize.js
const factorizeInplace = (n, /* out */ ls_base, ls_exp) => { // eslint-disable-line
  let ptr = 0;
  let q = n;

  // Separately take care 2 | q
  if (q % 2 === 0) {
    let e = 0;
    const p = 2;
    while (q % p === 0) {
      q /= p;
      e++;
    }
    ls_base[ptr] = p;
    ls_exp[ptr] = e;
    ptr++;
  }

  // Odd factors
  for (let p = 3; ; p += 2) {
    if ((p * p) > q) {
      break;
    }
    if (q % p === 0) {
      let e = 0;
      while (q % p === 0) {
        q /= p;
        e++;
      }
      ls_base[ptr] = p;
      ls_exp[ptr] = e;
      ptr++;
    }
  }

  // Left over
  if (q > 1) {
    ls_base[ptr] = q;
    ls_exp[ptr] = 1;
    ptr++;
  }

  return ptr;
};

const main = (n) => {
  console.log(factorize(n));
};

main(...process.argv.slice(2));
