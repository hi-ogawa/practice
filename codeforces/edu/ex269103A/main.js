//
// Rewrite main.py in javascript
//

const solve = (s, debug = 0) => {
  const n = s.length;
  const nn = n + 1;

  // Safe getter with 0 for out-of-bound
  const _ = (ls, i, k) => i < k ? ls[i] : 0;

  // Convert to numeric
  s = new TextEncoder().encode(s)

  // Suffix indices which we will sort
  const a = new Int32Array(nn);
  for (let i = 0; i < nn; i++) {
    a[i] = i;
  }

  // Prefix score
  let b = new Int32Array(nn)

  // Initialization (1-prefix)
  a.sort((i, j) => _(s, i, n) - _(s, j, n));
  {
    let e = _(s, a[0], n);
    let score = 0;
    for (let i = 0; i < nn; i++) {
      let e_i = _(s, a[i], n);
      if (e_i !== e) {
        e = e_i;
        score++;
      }
      b[a[i]] = score;
    }
  }

  if (debug) {
    console.log('m: 1, a:', ...a, 'b:', ...b);
  }

  // Recursion (m-prefix to 2m-prefix)
  let m = 1;
  let a_tmp = new Int32Array(nn);
  let b_tmp = new Int32Array(nn);
  let counts = new Int32Array(nn);
  let counts_cumsum = new Int32Array(nn + 1);
  while (m < n) {
    // 1. Sort 2m-prefix using m-prefix score by counting sort twice
    // 1.1. Counting sort (m, 2m)-fix
    for (let i = 0; i < nn; i++) {
      let score = _(b, a[i] + m, nn); // a[i] + m
      counts[score]++;
    }
    counts_cumsum[0] = 0;
    for (let i = 0; i < nn; i++) {
      counts_cumsum[i + 1] = counts[i] + counts_cumsum[i];
      counts[i] = 0;
    }
    for (let i = 0; i < nn; i++) {
      let score = _(b, a[i] + m, nn);
      a_tmp[counts_cumsum[score]] = a[i]; // a_tmp <-- a
      counts_cumsum[score] += 1;
    }
    // 1.1. Counting sort (0, m)-fix
    for (let i = 0; i < nn; i++) {
      let score = _(b, a_tmp[i], nn); // a_tmp[i]
      counts[score]++;
    }
    counts_cumsum[0] = 0;
    for (let i = 0; i < nn; i++) {
      counts_cumsum[i + 1] = counts[i] + counts_cumsum[i];
      counts[i] = 0;
    }
    for (let i = 0; i < nn; i++) {
      let score = _(b, a_tmp[i], nn);
      a[counts_cumsum[score]] = a_tmp[i]; // a <-- a_tmp
      counts_cumsum[score] += 1;
    }

    // 2. Make 2m-prefix score using m-prefix score
    {
      let e1 = _(b, a[0], nn);
      let e2 = _(b, a[0] + m, nn);
      let score = 0;
      for (let i = 1; i < nn; i++) {
        let e1_i = _(b, a[i], nn);
        let e2_i = _(b, a[i] + m, nn);
        if (e1_i !== e1 || e2_i !== e2) {
          e1 = e1_i;
          e2 = e2_i;
          score++;
        }
        b_tmp[a[i]] = score;
      }
      [b, b_tmp] = [b_tmp, b];
    }
    m *= 2;

    if (debug) {
      console.log(`m: ${m}, a:`, ...a, 'b:', ...b);
    }
  }

  return a;
};

const main = async (istr, ostr) => {
  const readline = require('readline');
  const it = readline.createInterface({input: istr})[Symbol.asyncIterator]();
  const getLine = async () => (await it.next()).value;
  const getMany = async () => (await getLine()).split(' ');

  const s = await getLine();
  const result = solve(s);
  ostr.write(`${result.join(' ')}\n`);
};

if (require.main === module) {
  main(process.stdin, process.stdout);
}

const test_0 = () => {
  const assert = require('assert');
  const s = 'ababba';
  assert.deepEqual(solve(s, 1), new Int32Array([6, 5, 0, 2, 4, 1, 3]));
};

const test_1 = () => {
  const inp = `
ababba
`.trimStart();
  const {Readable} = require('stream');
  main(Readable.from([inp]), process.stdout);
};

if (typeof module !== 'undefined') {
  module.exports = {test_0, test_1};
}
