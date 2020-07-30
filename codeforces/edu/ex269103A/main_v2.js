//
// Based on course's code example
//

const solve = (s, debug = 0) => {
  s += '$'; // Prepend "smaller" char value
  s = new TextEncoder().encode(s); // Convert to numeric
  const n = s.length;

  // Suffix indices which we will sort
  let a = new Int32Array(n);
  for (let i = 0; i < n; i++) {
    a[i] = i;
  }

  // Prefix score
  let b = new Int32Array(n);

  // Initialization (1-prefix)
  a.sort((i, j) => s[i] - s[j]);
  {
    b[a[0]] = 0;
    for (let i = 0; i < n; i++) {
      if (s[a[i]] === s[a[i - 1]]) {
        b[a[i]] = b[a[i - 1]];
        continue;
      }
      b[a[i]] = b[a[i - 1]] + 1;
    }
  }

  if (debug) {
    console.log('m: 1, a:', ...a, 'b:', ...b);
  }

  // Recursion (m-prefix to 2m-prefix)
  let a_tmp = new Int32Array(n);
  let b_tmp = new Int32Array(n);
  const counts = new Int32Array(n);
  const counts_cumsum = new Int32Array(n + 1);

  for (let m = 1; m < n; m <<= 1) {
    //
    // 1. Sort by [0, m)-prefix and [m, 2m)-infix scores
    //

    // 1.1. Sorting result of [m, 2m)-prefix is equivalent to current "a" itself
    //      since the set of [0, m)-prefices and [m, 2m)-prefices are permutation each other.
    //      Therefore, here NO-OP.

    // 1.2. Counting sort [0, m)-prefix
    for (let i = 0; i < n; i++) {
      const score = b[(a[i] - m + n) % n];
      counts[score]++;
    }
    counts_cumsum[0] = 0;
    for (let i = 0; i < n; i++) {
      counts_cumsum[i + 1] = counts[i] + counts_cumsum[i];
      counts[i] = 0;
    }
    for (let i = 0; i < n; i++) {
      const score = b[(a[i] - m + n) % n];
      a_tmp[counts_cumsum[score]] = (a[i] - m + n) % n;
      counts_cumsum[score] += 1;
    }
    [a, a_tmp] = [a_tmp, a];

    //
    // 2. Make 2m-prefix score using m-prefix score
    //
    b_tmp[a[0]] = 0;
    for (let i = 1; i < n; i++) {
      if (b[a[i]] === b[a[i - 1]] &&
          b[(a[i] + m) % n] === b[(a[i - 1] + m) % n]) {
        b_tmp[a[i]] = b_tmp[a[i - 1]];
        continue;
      }
      b_tmp[a[i]] = b_tmp[a[i - 1]] + 1;
    }
    [b, b_tmp] = [b_tmp, b];

    if (debug) {
      console.log(`m: ${m << 1}, a:`, ...a, 'b:', ...b);
    }
  }

  return a;
};

const main = async (istr, ostr) => {
  const readline = require('readline');
  const it = readline.createInterface({input: istr})[Symbol.asyncIterator]();
  const getLine = async () => (await it.next()).value;
  const getMany = async () => (await getLine()).split(' '); // eslint-disable-line

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
