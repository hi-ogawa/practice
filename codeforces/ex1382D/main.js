//
// Hopefully "find_subset_v2" will be faster by just using v8
//

const find_subset_v2 = (ls, target) => {
  const n = ls.length;
  const m = target + 1;
  const dp = new Uint8Array(n * m);
  const _ = (i, j) => i * m + j;

  dp[_(0, 0)] = 1;
  if (ls[0] < m) {
    dp[_(0, ls[0])] = 1;
  }

  for (let i = 1; i < n; i++) {
    for (let j = 0; j < m; j++) {
      let x = dp[_(i - 1, j)];
      if (ls[i] <= j) {
        x |= dp[_(i - 1, j - ls[i])];
      }
      dp[_(i, j)] = x;
    }
  }

  return dp[_(n - 1, target)];
};

const solve = (ls, debug = 0) => {
  const n = ls.length;

  // Make cumulative max and indices where cummax changes
  const cm = new Int32Array(n);
  const cm_id = [];
  let m = 0;
  for (let i = 0; i < n; i++) {
    if (ls[i] > m) {
      cm_id.push(i);
      m = ls[i];
    }
    cm[i] = m;
  }

  // Each region where cummax is same belong to same "unmerged" side
  const cm_id_diff = new Int32Array(cm_id.length);
  for (let i = 0; i < cm_id.length - 1; i++) {
    cm_id_diff[i] = cm_id[i + 1] - cm_id[i];
  }
  cm_id_diff[cm_id.length - 1] = n - cm_id.slice(-1)[0];

  if (debug) {
    console.log(ls, cm, cm_id, cm_id_diff);
  }

  // Find parition which makes "unmerged" pair same length
  const result = find_subset_v2(cm_id_diff, n / 2);
  return result ? 'YES' : 'NO';
};

const main = async (istr, ostr) => {
  const readline = require('readline');
  const it = readline.createInterface({input: istr})[Symbol.asyncIterator]();
  const next = async () => (await it.next()).value;
  const t = Number(await next());
  for (let i = 0; i < t; i++) {
    await next();
    const ls = new Int32Array((await next()).split(' ').map(Number));
    ostr.write(`${solve(ls)}\n`);
  }
};

if (require.main === module) {
  main(process.stdin, process.stdout);
}


// node -e 'require("./codeforces/ex1382D/main.js").test_1()'
const test_1 = () => {
  const inp = `
6
2
2 3 1 4
2
3 1 2 4
4
3 2 6 1 5 7 8 4
3
1 2 3 4 5 6
4
6 1 3 7 4 5 8 2
6
4 3 2 5 1 11 9 12 8 6 10 7
`.trimStart();
  const {Readable} = require('stream');
  main(Readable.from([inp]), process.stdout);
};

if (typeof module !== 'undefined') {
  module.exports = {test_1};
}
