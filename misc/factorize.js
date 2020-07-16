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

const main = (n) => {
  console.log(factorize(n));
};

main(...process.argv.slice(2));
