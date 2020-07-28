//
// Find (c_i) s.t.
//   \sum_i c_i = z
//   2 <= c_i <= w_i
//
const find_subset = (ws, z) => {
  const n = ws.length + 1;
  const m = z + 1;
  const dp = new Uint8Array(n * m);
  const _ = (i, j) => i * m + j;

  dp[_(0, 0)] = 1;
  for (let i = 0; i < ws.length; i++) {
    for (let j = 0; j <= z; j++) {
      if (!dp[_(i, j)]) {
        continue;
      }
      for (let jj = 2; jj <= ws[i]; jj++) {
        if (j + jj > z) {
          break;
        }
        dp[_(i + 1, j + jj)] = 1;
      }
    }
  }
  return dp[_(n - 1, z)];
};

const solve = (ls, x, y, debug = 0) => {
  // Count as multiset (Order of elements is irrelevant for solvability)
  const k = ls.length + 1;
  const ms = new Int32Array(k);
  for (let i = 0; i < ls.length; i++) {
    ms[ls[i]]++;
  }

  // Sort multiset
  const ms_sort = ms.slice().sort();
  const ms_max = ms_sort[ms_sort.length - 1];

  // Compute mixup-widths
  let mix_widths = [];
  let m = 0;
  for (let i = 0; i < ms_sort.length - 1; i++) {
    if (ms_sort[i] <= m) {
      continue;
    }
    for (let j = 0; j < ms_sort[i] - m; j++) {
      mix_widths.push(ms_sort.length - i);
    }
    m = ms_sort[i];
  }

  // Find "z" mixup of multiset
  const z = y - x;

  // TODO: restore found mixup
  const solvable = find_subset(mix_widths, z);

  return solvable && [];
};

const main = async (istr, ostr) => {
  const readline = require('readline');
  const it = readline.createInterface({input: istr})[Symbol.asyncIterator]();
  const next = async () => (await it.next()).value;
  const t = Number(await next());
  for (let i = 0; i < t; i++) {
    const [n, x, y] = (await next()).split(' ').map(Number);
    const ls = new Int32Array((await next()).split(' ').map(Number));
    const result = solve(ls, x, y);
    ostr.write(result ? `YES\n${result.join(' ')}\n` : 'NO\n');
  }
};

if (require.main === module) {
  main(process.stdin, process.stdout);
}

const test_0 = () => {
  const x = 3;
  const y = 4;
  const ls = [1, 1, 2, 1, 2];
  solve(ls, x, y);
};

const test_1 = () => {
  const inp = `
7
5 2 4
3 1 1 2 5
5 3 4
1 1 2 1 2
4 0 4
5 5 3 3
4 1 4
2 3 2 3
6 1 2
3 2 1 1 1 1
6 2 4
3 3 2 1 1 1
6 2 6
1 1 3 2 1 1
`.trimStart();
  const {Readable} = require('stream');
  main(Readable.from([inp]), process.stdout);
};

if (typeof module !== 'undefined') {
  module.exports = {test_0, test_1};
}
