// AC

// https://atcoder.jp/contests/abc334/tasks/abc334_e

use std::collections::BTreeSet;

fn main() {
    // ~ 1000
    let [h, w]: [usize; 2] = read_array();
    let board: Vec<Vec<char>> = (0..h)
        .map(|_| read_vec::<String>()[0].chars().collect())
        .collect();

    let (greens, reds): (Vec<(usize, usize)>, Vec<(usize, usize)>) = (0..h)
        .flat_map(|i| (0..w).map(move |j| (i, j)))
        .partition(|&(i, j)| board[i][j] == '#');

    // encode (usize, usize) -> usize
    let enc = |i: usize, j: usize| -> usize { i * w + j };

    // connected components by dsu
    let mut dsu = Dsu::new(enc(h, w));
    for &(i, j) in &greens {
        if i + 1 < h && board[i][j] == board[i + 1][j] {
            dsu.merge(enc(i, j), enc(i + 1, j));
        }
        if j + 1 < w {
            dsu.merge(enc(i, j), enc(i, j + 1));
        }
    }
    let components: BTreeSet<usize> = greens.iter().map(|&(i, j)| dsu.find(enc(i, j))).collect();
    let total = components.len();

    // check neighboring components of each "red"
    let mut result = Mint(0);
    for &(i, j) in &reds {
        let mut set: BTreeSet<usize> = BTreeSet::new();
        for (x, y) in get_neighbors((i, j), (h, w)) {
            if board[x][y] == '#' {
                set.insert(dsu.find(enc(x, y)));
            }
        }
        if set.len() == 0 {
            result += Mint(total + 1);
        } else {
            result += Mint(total - set.len() + 1);
        }
    }

    result /= Mint(reds.len());
    println!("{}", result.0);
}

fn get_neighbors((i, j): (usize, usize), (h, w): (usize, usize)) -> Vec<(usize, usize)> {
    let mut result: Vec<(usize, usize)> = vec![];
    if 0 < i {
        result.push((i - 1, j));
    }
    if i + 1 < h {
        result.push((i + 1, j));
    }
    if 0 < j {
        result.push((i, j - 1));
    }
    if j + 1 < w {
        result.push((i, j + 1));
    }
    result
}

/*
python misc/run.py atcoder/abc334/e/main.rs

%%%% begin
3 3
##.
#.#
#..
%%%%
499122178
%%%% end

%%%% begin
4 5
..#..
.###.
#####
..#..
%%%%
598946613
%%%% end

%%%% begin
3 4
#...
.#.#
..##
%%%%
285212675
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
// disjoint set union (dsu)
//

struct Dsu {
    parents: Vec<usize>,
}

impl Dsu {
    fn new(n: usize) -> Self {
        Self {
            parents: (0..n).collect(),
        }
    }

    fn find(&mut self, x: usize) -> usize {
        let mut p = self.parents[x];
        if p != x {
            p = self.find(p);
            self.parents[x] = p;
        }
        p
    }

    fn merge(&mut self, mut dst: usize, mut src: usize) {
        dst = self.find(dst);
        src = self.find(src);
        self.parents[src] = dst;
    }
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
