const solve = (data, H, W, K, debug = 0) => {
  const _ = (i, j) => i * W + j;
  let result = 0;

  // Enumerate 2^H, 2^W
  for (let rows = 0; rows < 2 ** H; rows++) {
    for (let cols = 0; cols < 2 ** W; cols++) {
      // Count surviving black entries
      let count = 0;
      for (let i = 0; i < H; i++) {
        for (let j = 0; j < W; j++) {
          if (data[_(i, j)] && ((1 << i) & rows) && ((1 << j) & cols)) {
            count++;
          }
        }
      }

      if (count === K) {
        result++;
      }
    }
  }
  return result;
};

const main = async (istr, ostr) => {
  const readline = require('readline');
  const it = readline.createInterface({input: istr})[Symbol.asyncIterator]();
  const getLine = async () => (await it.next()).value;
  const getMany = async () => (await getLine()).split(' ');

  const [H, W, K] = (await getMany()).map(Number);
  const data = new Uint8Array(H * W);
  const _ = (i, j) => i * W + j;
  for (let i = 0; i < H; i++) {
    const line = await getLine();
    for (let j = 0; j < W; j++) {
      data[_(i, j)] = line[j] === '#';
    }
  }
  const result = solve(data, H, W, K);
  ostr.write(`${result}\n`);
};

if (require.main === module) {
  main(process.stdin, process.stdout);
}


const test_1 = () => {
  const inp = `
6 6 8
..##..
.#..#.
#....#
######
#....#
#....#
`.trimStart();
  const {Readable} = require('stream');
  main(Readable.from([inp]), process.stdout);
};

if (typeof module !== 'undefined') {
  module.exports = {test_1};
}
