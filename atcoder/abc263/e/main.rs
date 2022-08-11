// AC

use std::{fmt::Debug, io, str::FromStr};

//
// modulo integer
//

const MODULO: usize = 998244353;

#[derive(Debug, Clone, Copy, Default)]
struct Mint(usize);

impl std::ops::Add for Mint {
    type Output = Self;
    fn add(self, rhs: Self) -> Self::Output {
        Self((self.0 + rhs.0) % MODULO)
    }
}

impl std::ops::Mul for Mint {
    type Output = Self;
    fn mul(self, rhs: Self) -> Self::Output {
        Self((self.0 * rhs.0) % MODULO)
    }
}

impl std::ops::Div for Mint {
    type Output = Self;

    fn div(self, rhs: Self) -> Self::Output {
        let rhs_inv = mod_pow(rhs, MODULO - 2);
        self * rhs_inv
    }
}

fn mod_pow(mut x: Mint, mut e: usize) -> Mint {
    let mut z = Mint(1);
    while e > 0 {
        if e & 1 > 0 {
            z = z * x;
        }
        x = x * x;
        e >>= 1;
    }
    z
}

//
// segment tree
//

type Node = Mint;

#[derive(Debug)]
struct SegmentTree {
    n: usize,
    data: Vec<Node>,
}

impl SegmentTree {
    fn new(n_orig: usize) -> Self {
        let mut n = 1;
        while n < n_orig {
            n *= 2;
        }
        Self {
            n,
            data: vec![Node::default(); 2 * n],
        }
    }

    fn get(&mut self, qi: usize) -> Node {
        self.data[qi + self.n]
    }

    fn set(&mut self, qi: usize, qv: Node) {
        let mut j = qi + self.n;
        self.data[j] = qv;
        j /= 2;
        while j > 1 {
            self.data[j] = self.data[2 * j] + self.data[2 * j + 1];
            j /= 2;
        }
    }

    fn reduce(&self, ql: usize, qr: usize) -> Node {
        let mut jl = ql + self.n;
        let mut jr = qr + self.n;
        let mut result_l = Node::default();
        let mut result_r = Node::default();
        while jl < jr {
            if jl & 1 > 0 {
                result_l = result_l + self.data[jl];
                jl += 1;
            }
            if jr & 1 > 0 {
                jr -= 1;
                result_r = self.data[jr] + result_r;
            }
            jl /= 2;
            jr /= 2;
        }
        result_l + result_r
    }
}

//
// main
//

fn main_case() -> io::Result<()> {
    let n = read_tokens::<usize>()?[0]; // [2, 2 x 10^5]
    let ls = read_tokens::<usize>()?;

    let mut tree = SegmentTree::new(n);

    for i in (0..(n - 1)).rev() {
        let a = ls[i];
        let e = tree.reduce(i + 1, i + a + 1);
        // solving
        //   Ei = ∑_j (Ej + 1) / (a + 1)
        //     = 1 + Ei / (a + 1) + ∑_(j != i) Ej / (a + 1)
        //    ⇕
        //   (1 - 1 / (a + 1)) Ei = 1 + ∑_(j != i) Ej / (a + 1)
        //    ⇕
        //   Ei = (1 + ∑_(j != i) Ej / (a + 1)) * (a + 1) / a
        let f = (Mint(1) + e / Mint(a + 1)) * Mint(a + 1) / Mint(a);
        // dbg!((i, a, e, f));
        tree.set(i, f);
    }
    // dbg!(&tree);

    let result = tree.get(0).0;
    println!("{}", result);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc263/e/main.rs

%%%% begin
3
1 1
%%%%
4
%%%% end

%%%% begin
5
3 1 2 1
%%%%
332748122
%%%% end
*/

//
// utils
//

fn read_tokens<F: FromStr>() -> io::Result<Vec<F>>
where
    <F as FromStr>::Err: Debug,
{
    let mut line = String::new();
    io::stdin().read_line(&mut line)?;
    let mut result: Vec<F> = Vec::new();
    for token in line.trim().split(" ") {
        let value: F = token
            .parse()
            .map_err(|e| io::Error::new(io::ErrorKind::Other, format!("{:?}", e)))?;
        result.push(value);
    }
    Ok(result)
}
