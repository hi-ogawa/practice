//
// node misc/pythagoras.js 1000 0
//

//
// Perspective projection (S1\{(1,0)} <-> R)
//   f : (x, y)               |--> z = y / (1 - x)
//   g | (z^2-1, 2z) / z^2+1  <--| z
//
// Taking z = q / p, we see,
//   g(q/p) = (q^2 - p^2, 2pq) / (q^2 + p^2)
//
// Therefore, we get Pythagoras triple (PT):
//   (a, b, c) = (q^2 - p^2, 2pq, q^2 + p^2)
//
//
// PROP. (Primitive PT neccessary condition)
//   Given
//     p, q: co-prime
//     p < q
//     p or q: even
//     (a, b, c) = (q^2 - p^2, 2pq, q^2 + p^2)
//   Then
//     1. a^2 + b^2 = c^2
//     2. a, b, c: co-prime
//     3. (a, b, c): (odd, even, odd)
//
//   PROOF
//     For 1, see above "Perspective projection".
//     For 2, it holds since
//       d | a    => (WLOG) d | p  => (WLOG) d | (p - q)  => d | q (contradiction)
//       d: prime != 2
//     For 3, it's obvious from 2.
//
//
// PROP. (Primitive PT sufficient condition)
//   Given
//     a^2 + b^2 = c^2
//     a, b, c: co-prime
//     (a, b, c): (odd, even, odd)
//     q / p = b / (c - a) (reduced to gcd(q, p) = 1)
//   Then,
//     1. p < q
//     2. p or q: even
//
//   PROOF.
//     For 1, we see
//       a + b > c  =>  b > c - a  =>  q / p = b / (c - a) > 1
//     For 2, noting
//       b^2 = c^2 - a^2 = (c - a) (c + a)
//     we have
//       q / p = b / (c - a) = (c + a) / b
//     so, it suffices to show (here, "†" denotes non-divisibility)
//       4 † b and 4 | (c - a)
//       or
//       4 | b and 4 † (c + a)
//     Indeed, it holds since whichever 4 † b or 4 | b, we have,
//       a, c: odd  => 4 | (c - a) and  4 † (c + a)
//                     or
//                     4 † (c - a) and  4 | (c + a)
//
//
// REMARK
//   1. Primitive PT (a, b, c) => only one of {a, b, c} is even (∵ mod 4 trick)
//   2. We have perimeter,
//        d = a + b + c = 2 (p + q) q
//        4p^2 < d < 4q^2
//
// TODO
//   1. Enumerate gcd(p, q) = 1 by co-prime tree
//

const gcd = (n, m) => { // n > m > 0
  for (;;) {
    const r = n % m;
    if (r === 0) {
      return m;
    }
    [n, m] = [m, r];
  }
};

const pythagoras = (c0, mode = 0) => {
  const {sqrt, floor} = Math;
  const p0 = floor(sqrt(c0 / 2));

  for (let p = 1; p <= p0; p++) {
    const p2 = p ** 2;
    for (let q = p + 1; ; q += 2) { // p + q: odd
      const q2 = q ** 2;
      if (p2 + q2 > c0) {
        break;
      }
      if (gcd(q, p) > 1) {
        continue;
      }
      const [a, b, c] = [
        q2 - p2,
        2 * p * q,
        q2 + p2,
      ];
      // Primitive
      console.log(a, b, c, `(q/p = ${q}/${p})`);
      if (mode >= 1) {
        // Non primitives
        for (let i = 2; i < c0 / c; i++) {
          console.log(i * a, i * b, i * c, `(i = ${i})`);
        }
      }
    }
  }
};

pythagoras(...process.argv.slice(2).map(Number));
