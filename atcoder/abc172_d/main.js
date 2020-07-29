//
// Compute via multiplicative property (sigma0)
// sigma(p^e) = 1 + e
// sigma(n.m) = sigma(n) sigma(m)  (for gcd(n, m) = 1)
//
const makeDivisor0 = (n) => {
  const a = new Uint8Array(n); // sieve
  const b = new Int32Array(n); // divisor sigma
  a[0] = 0;
  a[1] = 0;
  a.fill(1);
  b.fill(1);

  // Identify prime factor during sieve loop
  for (let p = 2; p < n; p++) {
    // non-prime
    if (a[p] === 0) {
      continue;
    }

    // Traverse n with ν_p(n) = e
    let sigma = 1;
    for (let pe = p; pe < n; pe *= p) {
      sigma++; // sigma = 1 + e

      for (let i = 1, pm = pe; pm < n; i++, pm += pe) {
        // Skip ν_p(n) > e
        if (i % p === 0) {
          continue;
        }
        a[pm] = 0;
        b[pm] *= sigma; // multiplicative by distinct prime factor
      }
    }
  }

  return b;
};

const solve = (n, debug = 0) => {
  const divisor = makeDivisor0(n + 1);
  let c = 0;
  for (let i = 1; i <= n; i++) {
    c += i * divisor[i];
  }
  return c;
};

const main = async (istr, ostr) => {
  const readline = require('readline');
  const it = readline.createInterface({input: istr})[Symbol.asyncIterator]();
  const getLine = async () => (await it.next()).value;
  const getMany = async () => (await getLine()).split(' '); // eslint-disable-line

  const n = Number(await getLine());
  const result = solve(n);
  ostr.write(`${result}\n`);
};

if (require.main === module) {
  main(process.stdin, process.stdout);
}


const test_1 = () => {
  const inp = `
10000000
`.trimStart();
  const {Readable} = require('stream');
  main(Readable.from([inp]), process.stdout);
};

if (typeof module !== 'undefined') {
  module.exports = {test_1};
}
