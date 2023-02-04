// AC

// https://atcoder.jp/contests/abc284/tasks/abc284_f

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // n ~ 10^6
    let n: usize = read_tokens()?[0];
    let t: Vec<u8> = read_tokens::<String>()?[0].bytes().collect();

    let root = Mint::new_random();
    let root_inv = root.inv();

    // precompute powers
    let mut pow: Vec<Mint> = vec![Mint(1); n + 1];
    let mut pow_inv: Vec<Mint> = vec![Mint(1); n + 1];
    for i in 0..n {
        pow[i + 1] = pow[i] * root;
    }
    for i in 0..n {
        pow_inv[i + 1] = pow_inv[i] * root_inv;
    }

    // hashes of first and last half of string
    let mut pre: Vec<Mint> = vec![Mint(0); n + 1];
    let mut rev: Vec<Mint> = vec![Mint(0); n + 1];

    for (i, &c) in t[0..n].iter().enumerate() {
        pre[i + 1] = pre[i] + Mint(c.into()) * pow[i];
    }

    for (i, &c) in t[n..].iter().rev().enumerate() {
        rev[i + 1] = rev[i] + Mint(c.into()) * pow[i];
    }

    for i in 0..n {
        let j = n - i;
        let pre_i = pre[i];
        let pre_j = (pre[n] - pre[i]) * pow_inv[i];
        let rev_i = (rev[n] - rev[j]) * pow_inv[j];
        let rev_j = rev[j];
        if pre_i == rev_i && pre_j == rev_j {
            let s = String::from_utf8(t[0..i].iter().chain(t[(n + i)..].iter()).copied().collect())
                .unwrap();
            println!("{}\n{}", s, i);
            return Ok(());
        }
    }

    println!("-1");
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc284/f/main.rs

%%%% begin
3
abcbac
%%%%
abc
2
%%%% end

%%%% begin
4
abababab
%%%%
abab
1
%%%% end

%%%% begin
3
agccga
%%%%
cga
0
%%%% end

%%%% begin
4
atcodeer
%%%%
-1
%%%% end
*/

//
// modulo integer (e.g. atcoder/abc262/e/main.rs)
//

const MODULO: usize = 998244353;

#[derive(PartialEq, Eq, Debug, Clone, Copy, Default)]
struct Mint(usize);

impl Mint {
    fn new_random() -> Self {
        let seed = std::time::SystemTime::UNIX_EPOCH
            .elapsed()
            .unwrap()
            .subsec_nanos() as usize;
        Mint(seed % (MODULO - 2) + 2)
    }

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

impl std::ops::SubAssign for Mint {
    fn sub_assign(&mut self, rhs: Self) {
        *self += -rhs;
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

impl std::ops::Neg for Mint {
    type Output = Self;
    fn neg(self) -> Self::Output {
        Mint(MODULO - self.0 % MODULO)
    }
}

impl std::ops::Add for Mint {
    type Output = Self;
    fn add(mut self, rhs: Self) -> Self::Output {
        self += rhs;
        self
    }
}

impl std::ops::Sub for Mint {
    type Output = Self;
    fn sub(mut self, rhs: Self) -> Self::Output {
        self -= rhs;
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
