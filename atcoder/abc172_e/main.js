// AFTER EDITORIAL

// NOTE: Integer is exact up to 2^53
// (uint32 * uint32) % uint32
const mul_mod = (x, y, m) => {
  const xl = x & 0xffff;
  const xh = x >>> 16;
  const yl = y & 0xffff;
  const yh = y >>> 16;
  const z1 = (((xh * yh) * 2 ** 16) % m) * 2 ** 16;
  const z2 = (xh * yl + xl * yh) * 2 ** 16;
  const z3 = xl * yl;
  return (z1 + z2 + z3) % m;
};

const fastExp = (base, exp, modulo) => {
  let result = 1;
  let base_exp = base;
  while (exp > 0) {
    if (exp & 1) {
      result = mul_mod(result, base_exp, modulo);
    }
    base_exp = mul_mod(base_exp, base_exp, modulo);
    exp = exp >> 1;
  }
  return result;
};

const makeFactorials = (n, modulo) => {
  const a = new Uint32Array(n + 1);
  const a_inv = new Uint32Array(n + 1);
  let k = 1;
  let k_inv = 1;
  a[0] = 1;
  a_inv[0] = 1;
  for (let i = 1; i <= n; i++) {
    const i_inv = fastExp(i, modulo - 2, modulo); // Inverse in Zp*
    k = mul_mod(k, i, modulo);
    k_inv = mul_mod(k_inv, i_inv, modulo);
    a[i] = k;
    a_inv[i] = k_inv;
  }
  return [a, a_inv];
};

const solve = (N, M, debug = 0) => {
  const modulo = 10 ** 9 + 7; // Prime
  const _XX = (x, y) => mul_mod(x, y, modulo);
  const [f, f_inv] = makeFactorials(M, modulo);

  if (debug) {
    for (let i = 0; i < f.length; i++) {
      console.log(i, f[i], f_inv[i], _XX(f[i], f_inv[i]));
    }
  }

  //
  // By inclusion-exclusion principle for the predicates Qi = { (A, B) | Ai = Bi }
  //   ¬⋁_i |Qi| = \sum_I (-1)^|I| |⋀_{i∈I} Qi|
  //             = \sum_k (-1)^k binom(N,k) |Q_I|
  //   where
  //      Q_I = ⋀_{i∈I} Qi = { (A, B) | ∀i ∈ I. Ai = Bi }
  //     |Q_I| = P(M, k) (P(M-k, N-k))^2
  //
  let result = 0;
  for (let k = 0; k <= N; k++) {
    const x = _XX(f[N], _XX(f_inv[N - k], f_inv[k]));
    const y = _XX(f[M], f_inv[M - k]);
    const z = _XX(f[M - k], f_inv[M - N]);
    const w = _XX(z, z);
    const xyw = _XX(x, _XX(y, w));
    if (k % 2) {
      result += modulo - xyw;
    } else {
      result += xyw;
    }
    result %= modulo;
  }
  return result;
};

const main = async (istr, ostr) => {
  const readline = require('readline');
  const it = readline.createInterface({input: istr})[Symbol.asyncIterator]();
  const getLine = async () => (await it.next()).value;
  const getMany = async () => (await getLine()).split(' ');

  const [N, M] = (await getMany()).map(Number);
  const result = solve(N, M);
  ostr.write(`${result}\n`);
};

if (require.main === module) {
  main(process.stdin, process.stdout);
}

const test_00 = () => {
  console.log(solve(10, 10, 1));
};

const _test = (inp) => {
  const {Readable} = require('stream');
  main(Readable.from([inp.trimStart()]), process.stdout);
};

const test_1 = () => _test(`
141421 356237
`);

const test_2 = () => _test(`
2 3
`);

const test_3 = () => _test(`
500000 500000
`);

if (typeof module !== 'undefined') {
  module.exports = {test_00, test_1, test_2, test_3};
}
