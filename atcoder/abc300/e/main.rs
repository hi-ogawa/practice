// AC

// https://atcoder.jp/contests/abc300/tasks/abc300_e

use std::collections::HashMap;

fn main() {
    // ~ 10^18
    let n: usize = read_tokens()[0];

    // factorize by 2, 3, 5
    let factors: Vec<usize> = vec![2, 3, 5];
    let powers: Vec<u32> = factors.iter().map(|&d| get_factor_power(n, d)).collect();

    // PROP.
    //   S = { (x, y, z) | 2^x 3^y 5^z ≤ n }
    //   then |S| ~ O(log(n)^3)

    // enumerate factors
    let mut ls: Vec<usize> = vec![];
    for p0 in 0..=powers[0] {
        for p1 in 0..=powers[1] {
            for p2 in 0..=powers[2] {
                ls.push(n / (factors[0].pow(p0) * factors[1].pow(p1) * factors[2].pow(p2)));
            }
        }
    }

    // PROP.
    //   f(x) = 1/6 (f(x) + f(2x) + ... + f(6x)) thus
    //   f(x) = 1/5 (f(2x) + ... + f(6x))
    let mut f: HashMap<usize, Mint> = HashMap::new();

    // dp by descending from n to 1
    ls.sort();
    assert!(ls.pop() == Some(n));

    f.insert(n, Mint(1));

    for &m in ls.iter().rev() {
        let acc = (2..=6)
            .filter_map(|x| f.get(&(x * m)))
            .fold(Mint(0), |acc, &el| acc + el);
        f.insert(m, acc / Mint(5));
    }

    let result = f.get(&1).copied().unwrap_or(Mint(0));
    println!("{}", result.0);
}

fn get_factor_power(mut x: usize, d: usize) -> u32 {
    let mut p = 0;
    while x % d == 0 {
        x = x / d;
        p += 1;
    }
    p
}

/*
python misc/run.py atcoder/abc300/e/main.rs

%%%% begin
6
%%%%
239578645
%%%% end

%%%% begin
7
%%%%
0
%%%% end

%%%% begin
300
%%%%
183676961
%%%% end

%%%% begin
979552051200000000
%%%%
812376310
%%%% end
*/

//
// utils
//

#[allow(dead_code)]
fn read_tokens<T: std::str::FromStr>() -> Vec<T>
where
    <T as std::str::FromStr>::Err: std::fmt::Debug,
{
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).unwrap();
    line.split_whitespace()
        .map(|s| s.parse().unwrap())
        .collect()
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
