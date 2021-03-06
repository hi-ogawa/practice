//
// node misc/prime.js 1000000
//

const makeSieve = (n) => {
  const a = new Uint8Array(n);
  a.fill(1);
  a[0] = 0;
  a[1] = 0;
  for (let i = 4; i < n; i += 2) {
    a[i] = 0;
  }

  const nn = Math.ceil(Math.sqrt(n));
  for (let i = 3; i < nn; i += 2) {
    if (a[i] == 0) {
      continue;
    }

    let ie = i * i;
    while (ie < n) {
      a[ie] = 0;
      ie += i;
    }
  }

  return a;
};

const printSieve = (a) => {
  let c = 0;
  for (let i = 0; i < a.length; i++) {
    if (a[i] == 1) {
      c += 1;
      console.log(`${c}: ${i}`);
    }
  }
};

const main = (n) => {
  printSieve(makeSieve(n));
};

main(...process.argv.slice(2));
