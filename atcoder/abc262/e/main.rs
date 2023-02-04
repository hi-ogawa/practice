// AFTER EDITORIAL, AC

use std::{fmt::Debug, io, str::FromStr};

//
// modulo integer
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

//
// combinatorics
//

static mut FACT: Vec<Mint> = Vec::new();
static mut INV_FACT: Vec<Mint> = Vec::new();

fn precompute_factorials(n: usize) {
    unsafe {
        FACT = vec![Mint(0); n + 1];
        INV_FACT = vec![Mint(0); n + 1];

        FACT[0] = Mint(1);
        for i in 1..=n {
            FACT[i] = FACT[i - 1] * Mint(i);
        }
        INV_FACT[n] = FACT[n].inv();
        for i in (1..=n).rev() {
            INV_FACT[i - 1] = INV_FACT[i] * Mint(i);
        }

        // dbg!(&FACT[0..10]);
        // dbg!(&INV_FACT[0..10]);
        // dbg!((0..10).map(|i| FACT[i] * INV_FACT[i]).collect::<Vec<_>>());
    }
}

fn comb(n: usize, m: usize) -> Mint {
    if n < m {
        Mint(0)
    } else {
        unsafe { FACT[n] * INV_FACT[n - m] * INV_FACT[m] }
    }
}

//
// main
//

fn main_case() -> io::Result<()> {
    let (n, m, k) = read_tokens::<usize>().map(|v| (v[0], v[1], v[2]))?; // ~ 2 x 10^5

    let mut degrees: Vec<usize> = vec![0; n];
    for _ in 0..m {
        let (u, v) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;
        degrees[u - 1] += 1;
        degrees[v - 1] += 1;
    }
    // dbg!(&degrees);

    // count vertices for each parity
    let p0 = degrees.iter().filter(|&x| x % 2 == 0).count();
    let p1 = n - p0;
    // dbg!((p0, p1));

    // count combination to pick even number out of p1
    let mut result = Mint(0);
    for i in 0..=(p1 / 2).min(k / 2) {
        result += comb(p0, k - 2 * i) * comb(p1, 2 * i);
    }
    println!("{}", result.0);

    Ok(())
}

fn main() -> io::Result<()> {
    precompute_factorials(1e6 as usize);
    main_case()
}

/*
python misc/run.py atcoder/abc262/e/main.rs

%%%% begin
4 4 2
1 2
1 3
2 3
3 4
%%%%
2
%%%% end

%%%% begin
10 10 3
1 2
2 4
1 5
3 6
3 9
4 10
7 8
9 10
5 9
3 4
%%%%
64
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
    for token in line.trim().split(' ') {
        let value: F = token
            .parse()
            .map_err(|e| io::Error::new(io::ErrorKind::Other, format!("{:?}", e)))?;
        result.push(value);
    }
    Ok(result)
}
