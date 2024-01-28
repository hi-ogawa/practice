// AC

// https://atcoder.jp/contests/abc326/tasks/abc326_e

fn main() {
    // n ~ 10^5
    let n: usize = read_vec()[0];
    let ls: Vec<usize> = read_vec();

    // PROP. (TODO: prove)
    //
    // defining
    //
    //   p(y) = probability to stop at y
    //
    // it holds that
    //
    //   p(0) = 1
    //   p(1) = 1 / n
    //   p(y + 1) = p(y) + p(y) / n

    let inv_n = Mint(n).inv();
    let mut p = inv_n;
    let mut result = p * Mint(ls[0]);
    for i in 1..n {
        p = p + p * inv_n;
        result += p * Mint(ls[i]);
    }
    println!("{}", result.0);
}

/*
python misc/run.py atcoder/abc326/e/main.rs

%%%% begin
3
3 2 6
%%%%
776412280
%%%% end

%%%% begin
1
998244352
%%%%
998244352
%%%% end

%%%% begin
9
3 14 159 2653 58979 323846 2643383 27950288 419716939
%%%%
545252774
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
