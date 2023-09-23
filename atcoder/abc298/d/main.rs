// AC

// https://atcoder.jp/contests/abc298/tasks/abc298_d

use std::collections::VecDeque;

fn main() {
    let n: usize = read_tokens()[0];

    let mut queue: VecDeque<usize> = VecDeque::new();
    let mut result = Mint(1);
    queue.push_back(1);

    for _ in 0..n {
        let input: Vec<String> = read_tokens();
        match input[0].as_str() {
            "1" => {
                let x: usize = input[1].parse().unwrap();
                queue.push_back(x);
                result = result * Mint(10) + Mint(x);
            }
            "2" => {
                let x = queue.pop_front().unwrap();
                result = result - Mint(x) * Mint(10).pow(queue.len());
            }
            "3" => {
                println!("{}", result.0);
            }
            _ => {}
        }
    }
}

/*
python misc/run.py atcoder/abc298/d/main.rs

%%%% begin
3
3
1 2
3
%%%%
1
12
%%%% end

%%%% begin
3
1 5
2
3
%%%%
5
%%%% end

%%%% begin
11
1 9
1 9
1 8
1 2
1 4
1 4
1 3
1 5
1 3
2
3
%%%%
0
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
