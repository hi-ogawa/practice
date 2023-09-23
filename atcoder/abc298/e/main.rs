// WIP

// https://atcoder.jp/contests/abc298/tasks/abc298_e

fn main() {
    // n ~ 100
    // p, q ~ 10
    let (n, a, b, p, q) = {
        let v: Vec<usize> = read_tokens();
        (v[0], v[1], v[2], v[3], v[4])
    };

    // dp(i, j, t) = answer when starting from (i, j) with t's turn
    let mut dp: Vec<Vec<[Mint; 2]>> = vec![vec![[Mint(0); 2]; n]; n];

    for i in 0..n {
        dp[i][n - 1][0] = Mint(0);
        dp[i][n - 1][1] = Mint(0);
        dp[n - 1][i][0] = Mint(1);
        dp[n - 1][i][1] = Mint(1);
    }

    for i in (0..n - 1).rev() {
        for j in (0..n - 1).rev() {
            for k in 1..=p {
                dp[i][j][0] = dp[i][j][0] + dp[(i + k).min(n - 1)][j][1];
            }
            dp[i][j][0] /= Mint(p);

            for k in 1..=q {
                dp[i][j][1] = dp[i][j][1] + dp[i][(j + k).min(n - 1)][0];
            }
            dp[i][j][1] /= Mint(q);
        }
    }

    let result = dp[a - 1][b - 1][0];
    println!("{}", result.0);
}

/*
python misc/run.py atcoder/abc298/e/main.rs

%%%% begin
4 2 3 3 2
%%%%
665496236
%%%% end

%%%% begin
6 4 2 1 1
%%%%
1
%%%% end

%%%% begin
100 1 1 10 10
%%%%
264077814
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
