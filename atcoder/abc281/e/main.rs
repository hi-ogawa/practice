// AC

// https://atcoder.jp/contests/abc281/tasks/abc281_e

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // ~ 10^5
    let (n, m, k) = read_tokens::<usize>().map(|v| (v[0], v[1], v[2]))?;
    // a \in [1, 10^9]
    let ls: Vec<usize> = read_tokens()?;

    // precompute order
    let mut order: Vec<usize> = (0..n).collect();
    order.sort_by_key(|&i| ls[i]);
    let mut order_inv: Vec<usize> = (0..n).collect();
    for i in 0..n {
        order_inv[order[i]] = i;
    }

    // segment trees
    let mut tree1 = SegmentTree::new(n); // to find k-th index
    let mut tree2 = SegmentTree::new(n); // to sum prefix

    for i in 0..m {
        tree1.set(order_inv[i], 1);
        tree2.set(order_inv[i], ls[i]);
    }

    for i in 0..(n - m + 1) {
        // find k-th by binary search
        let j = lower_bound(0, n, |i| tree1.reduce(0, i) >= k);

        // sum up to k-th index
        let result = tree2.reduce(0, j);
        print!("{}", result);

        // update
        if i + m < n {
            print!(" ");
            tree1.set(order_inv[i], 0);
            tree2.set(order_inv[i], 0);
            tree1.set(order_inv[i + m], 1);
            tree2.set(order_inv[i + m], ls[i + m]);
        }
    }
    println!("");

    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc281/e/main.rs

%%%% begin
6 4 3
3 1 4 1 5 9
%%%%
5 6 10
%%%% end

%%%% begin
10 6 3
12 2 17 11 19 8 4 3 6 20
%%%%
21 14 15 13 13
%%%% end
*/

//
// binary search
//

fn lower_bound<F: Fn(usize) -> bool>(mut x0: usize, mut x1: usize, f: F) -> usize {
    assert!(f(x1));
    assert!(!f(x0));
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
// utils
//

#[allow(dead_code)]
fn read_tokens<F: FromStr>() -> io::Result<Vec<F>>
where
    <F as FromStr>::Err: Debug,
{
    let mut line = String::new();
    io::stdin().read_line(&mut line)?;
    let mut result: Vec<F> = Vec::new();
    for token in line.trim().split(' ') {
        let value: F = token
            .parse()
            .map_err(|e| io::Error::new(io::ErrorKind::Other, format!("{:?}", e)))?;
        result.push(value);
    }
    Ok(result)
}
