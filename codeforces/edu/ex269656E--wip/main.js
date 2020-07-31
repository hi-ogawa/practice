// cf ex269103A/main_v2.js
const makeSuffixArray = (s, debug = 0) => {
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

const solve = (ls, debug = 0) => {
  ls.push(0); // Append smallest value
  const s = new Uint8Array(ls);
  const a = makeSuffixArray(s);
  const lcp = makeLcp(s, a);

  if (debug >= 2) {
    console.log(':: Suffixes and LCP ::');
    for (let i = 0; i < a.length; i++) {
      console.log(`[${a[i]},${lcp[i] || 0}]`, ...s.slice(a[i]));
    }
  }

  // Compute refrain score as "common prefix rectangle" of "suffix array grid".
  const n = lcp.length;
  let refrain = [0, 0, 0];
  const stack = []; // TODO: implement with typed array
  let ptr = 0;
  stack[ptr] = [0, 0]; // Pair (i, lcp[i])
  for (let i = 1; i < n; i++) {
    // Extend width
    if (lcp[i] > stack[ptr][1]) {
      stack[++ptr] = [i, lcp[i]];
      continue;
    }

    // Compute "rectangle area" when we're shrinking (thus "Height" is determined)
    while (lcp[i] < stack[ptr][1]) {
      const [i0, l0] = stack[ptr--];
      const score = (i + 1 - i0) * l0; // Height x Width
      if (score > refrain[0]) {
        refrain = [score, i0, l0];
      }
    }
  }

  while (0 < stack[ptr][1]) {
    const [i0, l0] = stack[ptr--];
    const score = (n + 1 - i0) * l0;
    if (score > refrain[0]) {
      refrain = [score, i0, l0];
    }
  }

  // Also check trivial case of whole string with 1-multiplicity
  if (refrain[0] < n) {
    return [n, n, s.slice(0, n)];
  }

  const [r0, r1, r2] = refrain;
  return [r0, r2, s.slice(a[r1], a[r1] + r2)];
};

const main = async (istr, ostr) => {
  const readline = require('readline');
  const it = readline.createInterface({input: istr})[Symbol.asyncIterator]();
  const getLine = async () => (await it.next()).value;
  const getMany = async () => (await getLine()).split(' '); // eslint-disable-line

  const [n, m] = (await getMany()).map(Number); // eslint-disable-line
  const ls = (await getMany()).map(Number);
  const result = solve(ls);
  ostr.write(`${result[0]}\n`);
  ostr.write(`${result[1]}\n`);
  ostr.write(`${result[2].join(' ')}\n`);
};

if (require.main === module) {
  main(process.stdin, process.stdout);
}

const test_00 = () => {
  const ls = '1 2 1 2 1 1 2 1'.split(' ').map(Number);
  console.log(solve(ls, 2));
};

const test_01 = () => {
  // TODO: it seems this get WA on (2, 3, 1) repeat example.
  // const ls = '1 1 1 1 1 1'.split(' ').map(Number);
  const ls = '2 3 1 2 3 1 2 3 1 2 3 1 2 3 1 2 3 1 2 3 1 2 3 1 2 3 1'.split(' ').map(Number); // eslint-disable-line
  console.log(solve(ls, 2));
};

const _test = (inp) => {
  const {Readable} = require('stream');
  main(Readable.from([inp.trimStart()]), process.stdout);
};

const test_1 = () => _test(`
8 3
1 2 1 2 1 1 2 1
`);

const test_2 = () => _test(`
1 1
1
`);

const test_3 = () => _test(`
6 2
1 2 1 2 1 2
`);

const test_4 = () => _test(`
6 2
1 1 1 1 1 1
`);

if (typeof module !== 'undefined') {
  module.exports = {test_00, test_01, test_1, test_2, test_3, test_4};
}
