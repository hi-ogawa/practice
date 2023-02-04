// TODO
// fenwick tree
// bit iteration

//
// recursive mutable closure macro
//

// TODO: currently signature (argument and return type) needs to be hard-coded
// TODO: RefCell/as_ptr might be undefined behavior
macro_rules! recursive_closure {
    ($N:ident, $E:expr) => {
        |x| {
            use std::cell::RefCell;

            struct Recurser<'a> {
                run: RefCell<&'a mut dyn FnMut(&Recurser, usize)>,
            }

            let mut recurser_impl = |recurser: &Recurser, x: usize| {
                let $N = |y: usize| (unsafe { &mut *recurser.run.as_ptr() })(recurser, y);
                $E(x)
            };

            let recurser = Recurser {
                run: RefCell::new(&mut recurser_impl),
            };

            (unsafe { &mut *recurser.run.as_ptr() })(&recurser, x)
        }
    };
}

//
// binary search
//

// min { x \in (x0, x1] | f(x) }
fn binary_search_min<F: Fn(usize) -> bool>(mut x0: usize, mut x1: usize, f: F) -> usize {
    assert!(f(x1));
    while x0 + 1 < x1 {
        let x = (x0 + x1 + 1) / 2;
        if f(x) {
            x1 = x;
        } else {
            x0 = x;
        }
    }
    x1
}

// max { x \in [x0, x1) | f(x) }
fn binary_search_max<F: Fn(usize) -> bool>(mut x0: usize, mut x1: usize, f: F) -> usize {
    assert!(f(x0));
    while x0 + 1 < x1 {
        let x = (x0 + x1) / 2;
        if f(x) {
            x0 = x;
        } else {
            x1 = x;
        }
    }
    x0
}

//
// disjoint set union (dsu) (e.g. atcoder/abc276/e/main.rs)
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
// segment tree
//

type Value = usize;

fn value_id() -> Value {
    0
}

fn value_multiply(lhs: Value, rhs: Value) -> Value {
    lhs + rhs
}

struct SegmentTree {
    n: usize,
    data: Vec<Value>,
}

impl SegmentTree {
    fn new(n_orig: usize) -> Self {
        let mut n = 1;
        while n < n_orig {
            n *= 2;
        }
        Self {
            n,
            data: vec![value_id(); 2 * n],
        }
    }

    fn set(&mut self, qi: usize, v: Value) {
        let mut j = qi + self.n;
        self.data[j] = v;
        while j > 1 {
            j /= 2;
            self.data[j] = value_multiply(self.data[2 * j], self.data[2 * j + 1]);
        }
    }

    fn reduce(&self, ql: usize, qr: usize) -> Value {
        let mut jl = ql + self.n;
        let mut jr = qr + self.n;
        let mut lhs = value_id();
        let mut rhs = value_id();
        while jl < jr {
            if jl & 1 == 1 {
                lhs = value_multiply(lhs, self.data[jl]);
                jl += 1;
            }
            if jr & 1 == 1 {
                jr -= 1;
                rhs = value_multiply(self.data[jr], rhs);
            }
            jl /= 2;
            jr /= 2;
        }
        value_multiply(lhs, rhs)
    }
}

impl std::fmt::Debug for SegmentTree {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let n = self.n;
        let d = (n as f64).log2().ceil() as usize;

        // find max width element
        let w = self
            .data
            .iter()
            .map(|v| format!("{}", v).len())
            .max()
            .unwrap();

        writeln!(f, "[")?;
        for i in 0..=d {
            let k = 1 << i;
            for j in 0..k {
                write!(
                    f,
                    "{:<width$}",
                    self.data[k + j],
                    width = if j == k - 1 { 0 } else { (w + 1) * (n / k) }
                )?;
            }
            writeln!(f, "")?
        }
        writeln!(f, "]")
    }
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

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_mint_inverse() {
        assert_eq!(Mint(18181) / Mint(18181), Mint(1));
    }

    #[test]
    fn test_dsu() {
        let n = 5;
        let mut dsu = Dsu::new(n);
        dsu.merge(0, 1);
        dsu.merge(2, 3);
        dsu.merge(1, 4);
        assert_eq!(
            (0..n).map(|x| dsu.find(x)).collect::<Vec<usize>>(),
            vec![0, 0, 2, 2, 0]
        );
    }

    #[test]
    fn test_segment_tree() {
        let mut tree = SegmentTree::new(5);
        tree.set(0, 1);
        tree.set(1, 2);
        tree.set(2, 3);
        tree.set(3, 5);
        tree.set(4, 7);
        assert_eq!(
            [(0, 3), (1, 4), (2, 5), (3, 6)]
                .iter()
                .map(|&(l, r)| tree.reduce(l, r))
                .collect::<Vec<usize>>(),
            vec![6, 10, 15, 12]
        );
        assert_eq!(
            format!("{:?}", &tree),
            r"[
18
11          7
3     8     7     0
1  2  3  5  7  0  0  0
]
"
        );
    }

    #[test]
    fn test_lower_bound() {
        let v = vec![0, 1, 3, 4, 7, 8];
        assert_eq!(binary_search_min(0, v.len() - 1, |i| v[i] * v[i] > 10), 3);
    }

    #[test]
    fn test_upper_bound() {
        let v = vec![0, 1, 3, 4, 7, 8];
        assert_eq!(binary_search_max(0, v.len(), |i| v[i] * v[i] < 10), 2);
    }

    #[test]
    fn test_recursive_closure() {
        let n = 5;
        let adj: Vec<Vec<usize>> = vec![vec![1, 2], vec![2], vec![4], vec![1], vec![0]];
        let mut visited = vec![false; n];
        let mut dfs = recursive_closure!(dfs, |x: usize| {
            visited[x] = true;
            for &y in &adj[x] {
                if !visited[y] {
                    dfs(y);
                }
            }
        });
        dfs(0);
        assert_eq!(visited, vec![true, true, true, false, true]);
    }
}
