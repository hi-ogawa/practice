// cf ex269103A/main_v2.js
const makeSuffixArray = (s, debug = 0) => {
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

// cf ex269118A/main.js
const findSubstring = (s, a, q, debug = 0) => {
  const nq = q.length;
  let i0 = 0;
  let i1 = a.length;
  let i = (i0 + i1) >> 1;
  while (i0 < i1) {
    if (debug) {
      console.log(`(i0, i, i1): (${i0}, ${i}, ${i1}), s: ${s[a[i]]}`); // eslint-disable-line
    }
    let forElse = true;
    for (let j = 0; j < nq; j++) {
      if (q[j] < s[a[i] + j]) {
        i1 = i;
        i = (i0 + i1) >> 1;
        forElse = false;
        break;
      }

      if (q[j] > s[a[i] + j]) {
        i0 = i + 1;
        i = (i0 + i1) >> 1;
        forElse = false;
        break;
      }
    }
    if (forElse) {
      return i;
    }
  }
  return -1;
};

// cf. ex269119A/main.js
const makeLcp = (s, a, debug = 0) => {
  const n = a.length;
  const lcp = new Int32Array(n - 1);

  // Permutation inverse
  const a_inv = new Int32Array(n);
  for (let i = 0; i < n; i++) {
    a_inv[a[i]] = i;
  }

  // Iterate from head of string (i.e. ai = 0, 1, ...)
  let k = 0;
  for (let ai = 0; ai < n - 1; ai++) {
    const i = a_inv[ai];
    if (debug) {
      console.log(`i: ${i}, a[i]: ${ai}, k: ${k}`);
    }
    let kk = k;
    while (s[ai + kk] === s[a[i - 1] + kk]) {
      kk++;
    }
    lcp[i - 1] = kk;
    k = Math.max(0, kk - 1); // known common length for the next
  }

  return lcp;
};

const solve = (s, ls, debug = 0) => {
  s += '$';
  const a = makeSuffixArray(s);
  const lcp = makeLcp(s, a);
  const result = [];

  for (const q of ls) {
    const i = findSubstring(s, a, q);
    if (debug) {
      console.log(`i: ${i}, a[i]: ${a[i]}, lcp[i]: ${lcp[i]}`);
    }
    // No substring match
    if (i === -1) {
      result.push(0);
      continue;
    }

    let count = 1;
    // Count to below
    for (let j = i; lcp[j] >= q.length && j <= lcp.length; j++) {
      count++;
    }
    // Count to above
    for (let j = i - 1; lcp[j] >= q.length && j >= 0; j--) {
      count++;
    }
    result.push(count);
  }

  return result;
};

const main = async (istr, ostr) => {
  const readline = require('readline');
  const it = readline.createInterface({input: istr})[Symbol.asyncIterator]();
  const getLine = async () => (await it.next()).value;
  const getMany = async () => (await getLine()).split(' '); // eslint-disable-line

  const s = await getLine();
  const n = Number(await getLine());
  const ls = [];
  for (let i = 0; i < n; i++) {
    ls.push(await getLine());
  }
  const result = solve(s, ls);
  ostr.write(`${result.join('\n')}\n`);
};

if (require.main === module) {
  main(process.stdin, process.stdout);
}

const test_00 = () => {
  const s = 'ababba';
  const ls = ['ba'];
  console.log(solve(s, ls, 1));
};

const _test = (inp) => {
  const {Readable} = require('stream');
  main(Readable.from([inp.trimStart()]), process.stdout);
};

const test_1 = () => _test(`
ababba
3
ba
baba
abba
`);

const test_2 = () => _test(`
itmouniversity
3
it
more
university
`);

if (typeof module !== 'undefined') {
  module.exports = {test_00, test_1, test_2};
}
