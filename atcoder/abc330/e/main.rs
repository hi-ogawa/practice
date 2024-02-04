// AC

// https://atcoder.jp/contests/abc330/tasks/abc330_e

fn main() {
    // PROP. MEX exists [0, n] by pigeon-hole principle

    // n ~ 10^5
    let [n, nq]: [usize; 2] = read_array();
    let mut ls: Vec<usize> = read_vec();

    // - track existance only up to "n"
    // - use prefix sum and binrary search to find MEX
    let mut tree = FenwickTree::new(n + 1);
    let mut counts: Vec<usize> = vec![0; n + 1];
    for &x in &ls {
        if x <= n {
            if counts[x] == 0 {
                tree.incr(x, 1);
            }
            counts[x] += 1;
        }
    }

    for _ in 0..nq {
        let [mut i, x]: [usize; 2] = read_array();
        i -= 1;
        if ls[i] != x {
            if ls[i] <= n {
                counts[ls[i]] -= 1;
                if counts[ls[i]] == 0 {
                    tree.decr(ls[i], 1);
                }
            }
            if x <= n {
                if counts[x] == 0 {
                    tree.incr(x, 1);
                }
                counts[x] += 1;
            }
            ls[i] = x;
        }
        let result = binary_search_min(0, n, |i| tree.sum_prefix(i + 1) < i + 1);
        println!("{}", result);
    }
}

/*
python misc/run.py atcoder/abc330/e/main.rs

%%%% begin
8 5
2 0 2 2 1 1 2 5
4 3
4 4
6 3
8 1000000000
2 1
%%%%
4
3
6
5
0
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
// Fenwick tree for sum
//

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

    // TODO(refactor): how to unify incr/decr implementation?
    fn decr(&mut self, i: usize, x: usize) {
        let mut k = i + 1;
        while k <= self.n {
            self.data[k] -= x;
            k = (k | (k - 1)) + 1;
        }
    }

    // [0, i)
    fn sum_prefix(&self, mut i: usize) -> usize {
        let mut result = 0;
        while i > 0 {
            result += self.data[i];
            i = i & (i - 1);
        }
        result
    }
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
