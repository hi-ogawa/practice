// AC

// https://atcoder.jp/contests/abc314/tasks/abc314_f

fn main() {
    // ~ 10^5
    let n: usize = read_vec()[0];

    // keep track of DSU merge process as
    // binrary tree with n leafs (2n - 1 vertices)
    let mut dsu = Dsu::new(n);
    for _ in 0..(n - 1) {
        let [p, q]: [usize; 2] = read_array();
        dsu.merge(p - 1, q - 1);
    }

    // traverse tree to compute sum along root->leaf path
    assert_eq!(dsu.next_id, 2 * n - 1);
    let mut result: Vec<Mint> = vec![Mint(0); 2 * n - 1];

    let dfs = RecursiveClosure::new(|dfs, (x, score): (usize, Mint)| {
        result[x] = score;
        if let Some(((y, size_y), (z, size_z))) = dsu.adj[x] {
            let size_y = Mint(size_y);
            let size_z = Mint(size_z);
            let size = size_y + size_z;
            dfs.call((y, score + size_y / size));
            dfs.call((z, score + size_z / size));
        }
    });

    let root = 2 * n - 2;
    dfs.call((root, Mint(0)));

    for i in 0..n {
        if i > 0 {
            print!(" ");
        }
        print!("{}", result[i].0);
    }
    println!();
}

struct Dsu {
    parents: Vec<usize>,
    sizes: Vec<usize>,
    next_id: usize,
    adj: Vec<Option<((usize, usize), (usize, usize))>>,
    node_map: Vec<usize>,
}

impl Dsu {
    fn new(n: usize) -> Dsu {
        Self {
            parents: (0..n).collect(),
            sizes: vec![1; n],
            next_id: n,
            adj: vec![None; 2 * n],
            node_map: (0..n).collect(),
        }
    }

    fn find(&mut self, x: usize) -> usize {
        let mut parent = self.parents[x];
        if parent != x {
            parent = self.find(parent);
            self.parents[x] = parent
        }
        parent
    }

    fn merge(&mut self, mut x: usize, mut y: usize) {
        // standard DSU
        x = self.find(x);
        y = self.find(y);
        let size_x = self.sizes[x];
        let size_y = self.sizes[y];
        self.sizes[x] += self.sizes[y];
        self.parents[y] = x;

        // keep track of merging history as binary tree edge
        let z = self.next_id;
        self.next_id += 1;
        self.adj[z] = Some(((self.node_map[x], size_x), (self.node_map[y], size_y)));
        self.node_map[x] = z;
    }
}

/*
python misc/run.py atcoder/abc314/f/main.rs

%%%% begin
5
1 2
4 3
5 3
1 4
%%%%
698771048 698771048 964969543 964969543 133099248
%%%% end

%%%% begin
15
9 2
8 10
13 6
12 11
7 10
4 10
14 2
5 4
1 15
15 2
6 9
8 11
6 3
2 8
%%%%
43970290 310168785 806914186 501498951 950708909 272140427 335124893 168750835 310168785 168750835 280459129 280459129 272140427 476542843 43970290
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
// modulo integer (e.g. atcoder/abc262/e/main.rs)
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
// recursive closure without macro
//

struct RecursiveClosure<F>(std::cell::RefCell<F>);

impl<F> RecursiveClosure<F> {
    fn new<Arg, Ret>(f: F) -> Self
    where
        F: FnMut(&dyn Callable<Arg, Ret>, Arg) -> Ret,
    {
        RecursiveClosure(std::cell::RefCell::new(f))
    }
}

trait Callable<Arg, Ret> {
    fn call(&self, arg: Arg) -> Ret;
}

impl<Arg, Ret, F> Callable<Arg, Ret> for RecursiveClosure<F>
where
    F: FnMut(&dyn Callable<Arg, Ret>, Arg) -> Ret,
{
    fn call(&self, arg: Arg) -> Ret {
        (unsafe { &mut *self.0.as_ptr() })(self, arg)
    }
}
