//
// recursive closure without macro
//
// - cons
//   - single argument (can workaround by tuple)
//   - explicitly `call`
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

// "simpler" implementation tends to hit either
//  - https://github.com/rust-lang/rust/issues/46062
//  - https://github.com/rust-lang/rust-analyzer/issues/8740
/* e.g.

struct RecursiveClosureV2<F>(RefCell<F>);

impl<F> RecursiveClosureV2<F> {
    fn new<Arg, Ret>(f: F) -> RecursiveClosureV2<F>
    where
        F: FnMut(&dyn Fn(Arg) -> Ret, Arg) -> Ret,
    {
        RecursiveClosureV2(RefCell::new(f))
    }

    fn call<Arg, Ret>(&self, arg: Arg) -> Ret
    where
        F: FnMut(&dyn Fn(Arg) -> Ret, Arg) -> Ret,
    {
        (unsafe { &mut *self.0.as_ptr() })(&|arg| self.call(arg), arg)
    }
}

struct RecursiveClosureV3<F>(RefCell<F>);

impl<F> RecursiveClosureV3<F> {
    fn new<Arg, Ret>(f: F) -> RecursiveClosureV3<F>
    where
        F: FnMut(&RecursiveClosureV3<F>, Arg) -> Ret,
    {
        RecursiveClosureV3(RefCell::new(f))
    }

    fn call<Arg, Ret>(&self, arg: Arg) -> Ret
    where
        F: FnMut(&RecursiveClosureV3<F>, Arg) -> Ret,
    {
        (unsafe { &mut *self.0.as_ptr() })(self, arg)
    }
}

*/

//
// recursive mutable closure macro
//

// cf. atcoder/abc285/d/main_v3.rs
// TODO: RefCell/as_ptr is this undefined behavior?
// TODO: each call requires setting up closure scope
// TODO: signature annotation might not be flexible compared to genuine closure syntax
macro_rules! recursive_closure {
    ($ID_RECURSE:ident, |$( $ID_ARGS:ident: $TYPE_ARGS:ty ),+| -> $TYPE_RETURN:ty $EXPR_BODY:block) => {
        |$( $ID_ARGS: $TYPE_ARGS ),*| {
            use std::cell::RefCell;

            struct __Recurser<'a> {
                __run: RefCell<&'a mut dyn FnMut(&__Recurser, $( $TYPE_ARGS ),*) -> $TYPE_RETURN>,
            }

            let mut __recurser_impl = |__recurser: &__Recurser, $( $ID_ARGS: $TYPE_ARGS ),*| {
                let $ID_RECURSE = |$( $ID_ARGS: $TYPE_ARGS ),*| {
                    (unsafe { &mut *__recurser.__run.as_ptr() })(__recurser, $( $ID_ARGS ),*)
                };
                $EXPR_BODY
            };

            let __recurser = __Recurser {
                __run: RefCell::new(&mut __recurser_impl),
            };

            (unsafe { &mut *__recurser.__run.as_ptr() })(&__recurser, $( $ID_ARGS ),*)
        }
    };
}

//
// binary search
//

// min { x \in [x0, x1] | f(x) }
fn binary_search_min<F: Fn(usize) -> bool>(mut x0: usize, mut x1: usize, f: F) -> usize {
    assert!(f(x1));
    while x0 < x1 {
        let x = (x0 + x1) / 2;
        if f(x) {
            x1 = x;
        } else {
            x0 = x + 1;
        }
    }
    x1
}

// max { x \in [x0, x1] | f(x) }
fn binary_search_max<F: Fn(usize) -> bool>(mut x0: usize, mut x1: usize, f: F) -> usize {
    assert!(f(x0));
    while x0 < x1 {
        let x = (x0 + x1 + 1) / 2;
        if f(x) {
            x0 = x;
        } else {
            x1 = x - 1;
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

// Fenwick tree for sum
struct FenwickTree {
    n: usize,
    data: Vec<usize>,
}

impl FenwickTree {
    fn new(n: usize) -> Self {
        Self {
            n,
            data: vec![0; n + 1], // use 1-based index internally since zero-based index doesn't go well with usize
        }
    }

    fn incr(&mut self, i: usize, x: usize) {
        let mut k = i + 1;
        while k <= self.n {
            self.data[k] += x;
            k = (k | (k - 1)) + 1;
        }
    }

    // [0, i)
    fn reduce_prefix(&self, mut i: usize) -> usize {
        let mut result = 0;
        while i > 0 {
            result += self.data[i];
            i = i & (i - 1);
        }
        result
    }

    // [l, r)
    fn reduce(&self, l: usize, r: usize) -> usize {
        self.reduce_prefix(r) - self.reduce_prefix(l)
    }
}

//
// https://en.cppreference.com/w/cpp/algorithm/next_permutation
//

fn next_permutation(v: &mut Vec<usize>) -> bool {
    //
    // 1. find suffix s.t.
    //
    // ... x  <  y1 >= .. >= yk >= .. >= yn
    //
    // where k = max { i | y_i > x }
    //
    // 2. by swapping (x, yk),
    //
    // ... yk <= y1 >= .. >= x  >= .. >= yn
    //
    // 3. by reversing (y1, ..., yn)
    //
    // ... yk <= yn <= .. <= x  <= .. <= r1
    //

    // 1.0. find descending suffix
    let n = v.len();
    let i = (1..n).rev().find(|&i| v[i - 1] < v[i]);
    if i.is_none() {
        return false;
    }

    // 1.1. find y_k > x
    let i = i.unwrap();
    let j = i + v[i..n].partition_point(|&y| y > v[i - 1]) - 1;

    // 2.
    v.swap(i - 1, j);

    // 3.
    for d in 0..((n - i) / 2) {
        v.swap(i + d, n - 1 - d);
    }
    true
}

//
// bit iterator
//

fn bit_iterator(mut s: usize) -> impl Iterator<Item = usize> {
    std::iter::from_fn(move || {
        if s == 0 {
            None
        } else {
            let next = s.trailing_zeros();
            s = s & (s - 1);
            Some(next as usize)
        }
    })
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
// multiset
//

#[derive(Debug)]
struct Multiset<K> {
    map: std::collections::BTreeMap<K, usize>,
}

impl<K: Ord> Multiset<K> {
    fn new() -> Self {
        Self {
            map: std::collections::BTreeMap::new(),
        }
    }

    fn insert(&mut self, k: K) {
        *self.map.entry(k).or_default() += 1;
    }

    // TODO: test
    fn remove(&mut self, k: &K) {
        if let Some(v) = self.map.get_mut(k) {
            assert!(*v > 0);
            if *v > 1 {
                *v -= 1;
            } else {
                self.map.remove(&k);
            }
        }
    }

    fn first(&self) -> Option<&K> {
        self.map.first_key_value().map(|kv| kv.0)
    }

    fn last(&self) -> Option<&K> {
        self.map.last_key_value().map(|kv| kv.0)
    }

    // TODO: can we return `Option<&K>`
    fn pop_first(&mut self) {
        if let Some(mut entry) = self.map.first_entry() {
            let v = entry.get_mut();
            assert!(*v > 0);
            if *v > 1 {
                *v -= 1;
            } else {
                entry.remove();
            }
        }
    }

    fn pop_last(&mut self) {
        if let Some(mut entry) = self.map.last_entry() {
            let v = entry.get_mut();
            assert!(*v > 0);
            if *v > 1 {
                *v -= 1;
            } else {
                entry.remove();
            }
        }
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
            [(0, 3), (1, 4), (2, 5), (3, 5)]
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
    fn test_fenwick_tree() {
        let mut tree = FenwickTree::new(5);
        tree.incr(0, 1);
        tree.incr(1, 2);
        tree.incr(2, 3);
        tree.incr(3, 5);
        tree.incr(4, 7);
        assert_eq!(
            [(0, 3), (1, 4), (2, 5), (3, 5)]
                .iter()
                .map(|&(l, r)| tree.reduce(l, r))
                .collect::<Vec<usize>>(),
            vec![6, 10, 15, 12]
        );
    }

    #[test]
    fn test_lower_bound() {
        let v = vec![0, 1, 3, 4, 7, 8];
        assert_eq!(binary_search_min(0, v.len() - 1, |i| v[i] * v[i] > 10), 3);
        assert_eq!(binary_search_min(0, 1, |i| v[i] >= 0), 0);
        assert_eq!(binary_search_min(0, 1, |i| v[i] >= 1), 1);
    }

    #[test]
    fn test_upper_bound() {
        let v = vec![0, 1, 3, 4, 7, 8];
        assert_eq!(binary_search_max(0, v.len() - 1, |i| v[i] * v[i] < 10), 2);
        assert_eq!(binary_search_max(0, 1, |i| v[i] < 1), 0);
        assert_eq!(binary_search_max(0, 1, |i| v[i] < 2), 1);
    }

    #[test]
    fn test_recursive_closure_mutable() {
        let n = 5;
        let adj: Vec<Vec<usize>> = vec![vec![1, 2], vec![2], vec![4], vec![1], vec![0]];
        let mut visited = vec![false; n];
        let mut dfs = recursive_closure!(dfs, |x: usize| -> () {
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

    #[test]
    fn test_recursive_closure_multiple_arguments() {
        // ackermann
        let f = recursive_closure!(f, |m: usize, n: usize| -> usize {
            match (m, n) {
                (0, _) => n + 1,
                (_, 0) => f(m - 1, 1),
                _ => f(m - 1, f(m, n - 1)),
            }
        });
        assert_eq!(f(3, 4), 125);
    }

    #[test]
    fn test_recursive_closure_v2_mutable() {
        let n = 5;
        let adj: Vec<Vec<usize>> = vec![vec![1, 2], vec![2], vec![4], vec![1], vec![0]];
        let mut visited = vec![false; n];
        let dfs = RecursiveClosure::new(|dfs, x: usize| {
            visited[x] = true;
            for &y in &adj[x] {
                if !visited[y] {
                    dfs.call(y);
                }
            }
        });
        dfs.call(0);
        assert_eq!(visited, vec![true, true, true, false, true]);
    }

    #[test]
    fn test_recursive_closure_v2_multiple_arguments() {
        // ackermann
        let f = RecursiveClosure::new(|f, (m, n): (usize, usize)| -> usize {
            match (m, n) {
                (0, _) => n + 1,
                (_, 0) => f.call((m - 1, 1)),
                _ => f.call((m - 1, f.call((m, n - 1)))),
            }
        });
        assert_eq!(f.call((3, 4)), 125);
    }

    #[test]
    fn test_next_permutation() {
        let mut perm: Vec<usize> = (0..3).collect();
        let mut perms: Vec<Vec<usize>> = vec![];
        loop {
            perms.push(perm.clone());
            if !next_permutation(&mut perm) {
                break;
            }
        }
        assert_eq!(
            perms,
            vec![
                vec![0, 1, 2],
                vec![0, 2, 1],
                vec![1, 0, 2],
                vec![1, 2, 0],
                vec![2, 0, 1],
                vec![2, 1, 0],
            ]
        )
    }

    #[test]
    fn test_bit_iterator() {
        assert_eq!(bit_iterator(0).collect::<Vec<_>>(), vec![]);
        assert_eq!(bit_iterator(0b0101).collect::<Vec<_>>(), vec![0, 2]);
    }

    #[test]
    fn test_multiset() {
        let mut set: Multiset<usize> = Multiset::new();
        assert_eq!(set.first(), None);
        assert_eq!(set.last(), None);
        set.insert(1);
        set.insert(1);
        set.insert(2);
        set.insert(3);
        assert_eq!(set.first(), Some(&1));
        assert_eq!(set.last(), Some(&3));
        set.pop_last();
        assert_eq!(set.first(), Some(&1));
        assert_eq!(set.last(), Some(&2));
        set.pop_first();
        assert_eq!(set.first(), Some(&1));
        assert_eq!(set.last(), Some(&2));
        set.remove(&1);
        assert_eq!(set.first(), Some(&2));
        assert_eq!(set.last(), Some(&2));
        set.remove(&2);
        assert_eq!(set.first(), None);
        assert_eq!(set.last(), None);
    }
}
