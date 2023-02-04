// AC

// https://atcoder.jp/contests/abc276/tasks/abc276_f

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // n ~ 2 x 10^5
    let n: usize = read_tokens()?[0];
    // a ~ 2 x 10^5
    let ls: Vec<usize> = read_tokens()?;

    /*
     *   E[max(x, y)]
     * = ∑_{x, y} p(x, y) max(x, y)
     * = (1 / k^2) ∑_{x, y} max(x, y)   (note: p(x, y) = p(x) p(y) = 1 / k^2)
     * = (1 / k^2) (1 * x_1 + 3 * x_2 + 5 * x_3 + ... + (2 * k - 1) * x_k)  (where (x_1 ... x_k) = sort(a_1 .. a_k))
     */

    // pre-compute ordering
    let mut order: Vec<usize> = (0..n).collect();
    order.sort_by_key(|&i| ls[i]);

    let mut order_inv: Vec<usize> = vec![0; n];
    for i in 0..n {
        order_inv[order[i]] = i;
    }

    let mut tmp_sum = Mint(0);
    let mut tree1 = SegmentTree::new(n); // existence
    let mut tree2 = SegmentTree::new(n); // sum

    for k in 1..=n {
        let i = k - 1;
        let o = order_inv[i];

        let count = tree1.reduce(0, o); // find where it's inserted
        let incr = tree2.reduce(o, n); // the higher sum gets bonus
        tmp_sum += (Mint(2) * count + Mint(1)) * Mint(ls[i]) + Mint(2) * incr;

        tree1.set(o, Mint(1));
        tree2.set(o, Mint(ls[i]));

        let result = tmp_sum / (Mint(k) * Mint(k));
        println!("{}", result.0);
    }

    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc276/f/main.rs

%%%% begin
3
5 7 5
%%%%
5
499122183
443664163
%%%% end

%%%% begin
7
22 75 26 45 72 81 47
%%%%
22
249561150
110916092
873463862
279508479
360477194
529680742
%%%% end
*/

//
// modulo integer
//

const MODULO: usize = 998244353;

#[derive(PartialEq, Eq, Debug, Clone, Copy, Default)]
struct Mint(usize);

impl Mint {
    fn pow(&self, mut e: usize) -> Self {
        let mut x = *self;
        let mut y = Mint(1);
        while e > 0 {
            if e & 1 > 0 {
                y = y * x;
            }
            x = x * x;
            e >>= 1;
        }
        y
    }

    fn inv(&self) -> Self {
        self.pow(MODULO - 2)
    }
}

impl std::ops::AddAssign for Mint {
    fn add_assign(&mut self, rhs: Self) {
        self.0 = (self.0 + rhs.0) % MODULO;
    }
}

impl std::ops::MulAssign for Mint {
    fn mul_assign(&mut self, rhs: Self) {
        self.0 = (self.0 * rhs.0) % MODULO;
    }
}

impl std::ops::DivAssign for Mint {
    fn div_assign(&mut self, rhs: Self) {
        *self *= rhs.inv();
    }
}

impl std::ops::Add for Mint {
    type Output = Self;
    fn add(mut self, rhs: Self) -> Self::Output {
        self += rhs;
        self
    }
}

impl std::ops::Mul for Mint {
    type Output = Self;
    fn mul(mut self, rhs: Self) -> Self::Output {
        self *= rhs;
        self
    }
}

impl std::ops::Div for Mint {
    type Output = Self;
    fn div(mut self, rhs: Self) -> Self::Output {
        self /= rhs;
        self
    }
}

//
// segment tree
//
type Value = Mint;

fn value_id() -> Value {
    Mint(0)
}

fn value_multiply(lhs: Value, rhs: Value) -> Value {
    lhs + rhs
}

struct SegmentTree {
    n: usize,
    data: Vec<Value>,
}

impl SegmentTree {
    fn new(n: usize) -> Self {
        let n = ceil_pow2(n);
        Self {
            n,
            data: vec![value_id(); 2 * n],
        }
    }

    fn set(&mut self, qi: usize, v: Value) {
        let mut j = qi + self.n;
        self.data[j] = v;
        while j > 1 {
            j /= 2;
            self.data[j] = value_multiply(self.data[2 * j], self.data[2 * j + 1]);
        }
    }

    fn reduce(&self, ql: usize, qr: usize) -> Value {
        let mut jl = ql + self.n;
        let mut jr = qr + self.n;
        let mut lhs = value_id();
        let mut rhs = value_id();
        while jl < jr {
            if jl & 1 == 1 {
                lhs = value_multiply(lhs, self.data[jl]);
                jl += 1;
            }
            if jr & 1 == 1 {
                jr -= 1;
                rhs = value_multiply(self.data[jr], rhs);
            }
            jl /= 2;
            jr /= 2;
        }
        value_multiply(lhs, rhs)
    }
}

fn ceil_pow2(n: usize) -> usize {
    let mut x = 1;
    while x < n {
        x *= 2;
    }
    x
}

//
// utils
//

#[allow(dead_code)]
fn read_tokens<F: FromStr>() -> io::Result<Vec<F>>
where
    <F as FromStr>::Err: Debug,
{
    let mut line = String::new();
    io::stdin().read_line(&mut line)?;
    let mut result: Vec<F> = Vec::new();
    for token in line.trim().split(' ') {
        let value: F = token
            .parse()
            .map_err(|e| io::Error::new(io::ErrorKind::Other, format!("{:?}", e)))?;
        result.push(value);
    }
    Ok(result)
}
