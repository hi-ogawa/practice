// TODO
// fenwick tree
// segment tree
// bit iteration

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
    }
}
