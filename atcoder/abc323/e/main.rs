// AC

// https://atcoder.jp/contests/abc323/tasks/abc323_e

fn main() {
    // n ~ 10^3
    // x ~ 10^4
    let [n, x]: [usize; 2] = read_array();
    let ls: Vec<usize> = read_vec();

    // dp(t) = (probability to start new song at time "t")
    let mut dp: Vec<Mint> = vec![Mint(0); x + 1];
    dp[0] = Mint(1);

    let n_inv = Mint(n).inv(); // perf: constant division

    for t in 0..=x {
        for &v in &ls {
            if t >= v {
                dp[t] = dp[t] + dp[t - v] * n_inv;
            }
        }
    }

    // sum probability of starting 1st song between (x - t1, x)
    let result = (x.saturating_sub(ls[0] - 1)..=x)
        .map(|t| dp[t] * n_inv)
        .fold(Mint(0), |x, y| x + y);
    println!("{}", result.0);
}

/*
python misc/run.py atcoder/abc323/e/main.rs

%%%% begin
3 6
3 5 6
%%%%
369720131
%%%% end

%%%% begin
5 0
1 2 1 2 1
%%%%
598946612
%%%% end

%%%% begin
5 10000
1 2 3 4 5
%%%%
586965467
%%%% end
*/

//
// utils
//

#[allow(dead_code)]
fn read_vec<T: std::str::FromStr>() -> Vec<T> {
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).unwrap();
    line.split_whitespace()
        .map(|s| s.parse().ok().unwrap())
        .collect()
}

#[allow(dead_code)]
fn read_array<T: std::str::FromStr, const LEN: usize>() -> [T; LEN] {
    #[allow(unused_imports)]
    use std::convert::TryInto;
    read_vec::<T>().try_into().ok().unwrap()
}

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
