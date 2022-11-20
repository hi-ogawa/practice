// AC

// https://atcoder.jp/contests/abc275/tasks/abc275_e

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // n, k ~ 10^3
    // m ~ 10
    let (n, m, k) = read_tokens::<usize>().map(|v| (v[0], v[1], v[2]))?;

    let mut result = Mint(0);
    let mut probs: Vec<Mint> = vec![Mint(0); n];
    probs[0] = Mint(1);

    // brute-force O(n m k)
    for _ in 0..k {
        let mut next = vec![Mint(0); n];
        for i in 0..n {
            let p = probs[i] / Mint(m);
            for j in 1..=m {
                if i + j < n {
                    next[i + j] += p;
                }
                if i + j == n {
                    result += p;
                }
                if i + j > n {
                    next[n - (i + j - n)] += p;
                }
            }
        }
        probs = next;
    }

    println!("{}", result.0);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc275/e/main.rs

%%%% begin
2 2 1
%%%%
499122177
%%%% end

%%%% begin
10 5 6
%%%%
184124175
%%%% end

%%%% begin
100 1 99
%%%%
0
%%%% end
*/

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
    for token in line.trim().split(" ") {
        let value: F = token
            .parse()
            .map_err(|e| io::Error::new(io::ErrorKind::Other, format!("{:?}", e)))?;
        result.push(value);
    }
    Ok(result)
}

//
// modulo integer (misc/templates/lib.rs)
//

const MODULO: usize = 998244353;

#[derive(Debug, Clone, Copy)]
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
