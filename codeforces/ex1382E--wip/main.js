// AFTER EDITORIAL

//
// TODO: Realize solvable shuffle/replacement after solvability is determined.
//

const solve = (ls, x, y, debug = 0) => {
  const n = ls.length;
  const z = y - x; // Amount needs to be shuffled
  const w = n - y; // Amount needs to be thrown away

  // Count each colors
  const k = n + 2;
  const ms = new Int32Array(k);
  for (let i = 0; i < ls.length; i++) {
    ms[ls[i]]++;
  }

  // Sort counts
  const ms_sort = ms.slice().sort();

  // "transpose" counting histogram
  const ms_sort_T = [];
  {
    let m = 0;
    for (let i = 0; i < ms_sort.length; i++) {
      if (ms_sort[i] <= m) {
        continue;
      }
      for (let j = 0; j < ms_sort[i] - m; j++) {
        ms_sort_T.push(ms_sort.length - i);
      }
      m = ms_sort[i];
    }
  }

  // Determine correct "x" positions (subtract from color with high multiplicity)
  const ms_sort_sub_x = ms_sort.slice();
  {
    let xx = x;
    for (let i = ms_sort_T.length - 1; i >= 0; i--) {
      if (ms_sort_T[i] > xx) {
        for (let j = ms_sort_T[i]; j > ms_sort_T[i] - xx; j--) {
          ms_sort_sub_x[k - j]--;
        }
        ms_sort_T[i] -= xx;
        break;
      }
      for (let j = ms_sort_T[i]; j > 0; j--) {
        ms_sort_sub_x[k - j]--;
      }
      xx -= ms_sort_T[i];
      ms_sort_T[i] = 0;
    }
  }

  // Check if maximum shuffle length exceeds z
  const f = ms_sort_sub_x[ms_sort_sub_x.length - 1];
  const nx = n - x;
  const shuffle_max = Math.min(2 * (nx - f), nx);
  const solvable = shuffle_max >= z;

  // TODO: realize such solvable shuffle/replacement
  return solvable? ['???'] : 0;
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
  const x = 2;
  const y = 6;
  const ls = [1, 1, 3, 2, 1, 1];
  console.log(solve(ls, x, y));
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
