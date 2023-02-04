// AFTER EDITORIAL, AC

// https://atcoder.jp/contests/abc283/tasks/abc283_f

use std::{fmt::Debug, io, str::FromStr};

const BIG_VALUE: isize = 1e9 as isize; // since std::isize::MAX might be prone to over/underflow

fn main_case() -> io::Result<()> {
    // 10^5
    let n: usize = read_tokens()?[0];
    let ls: Vec<isize> = read_tokens()?;

    // sorting
    let mut order: Vec<usize> = (0..n).collect();
    order.sort_by_key(|&i| ls[i]);

    // segment tree for range minimum
    let mut tree = SegmentTree::new(n);
    let mut result: Vec<isize> = vec![BIG_VALUE; n];

    // do almost same thing for 4 times

    // f(i) = min { |Pj - Pi| + |j - i| | i < j and Pi <= Pj }
    //              ^^^^^^^^^^^^^^^^^^^
    //              (Pj + j) - Pi - i
    {
        for j in 0..n {
            tree.set(j, ls[j] + j as isize);
        }

        // process from smaller Pi to exclude the case of "Pj <= Pi" during later loop
        for &i in &order {
            let f = tree.reduce(i + 1, n) - ls[i] - i as isize;
            result[i] = result[i].min(f);
            tree.set(i, BIG_VALUE); // dummy value to exclude from later "minimum"
        }
    }

    // f(i) = min { |Pj - Pi| + |j - i| | i < j and Pi >= Pj }
    //              ^^^^^^^^^^^^^^^^^^^
    //              (-Pj + j) + Pi - i
    {
        for j in 0..n {
            tree.set(j, -ls[j] + j as isize);
        }

        for &i in order.iter().rev() {
            let f = tree.reduce(i + 1, n) + ls[i] - i as isize;
            result[i] = result[i].min(f);
            tree.set(i, BIG_VALUE);
        }
    }

    // f(i) = min { |Pj - Pi| + |j - i| | i > j and Pi <= Pj }
    //              ^^^^^^^^^^^^^^^^^^^
    //              (Pj - j) - Pi + i
    {
        for j in 0..n {
            tree.set(j, ls[j] - j as isize);
        }

        for &i in &order {
            let f = tree.reduce(0, i) - ls[i] + i as isize;
            result[i] = result[i].min(f);
            tree.set(i, BIG_VALUE);
        }
    }

    // f(i) = min { |Pj - Pi| + |j - i| | i > j and Pi >= Pj }
    //              ^^^^^^^^^^^^^^^^^^^
    //              (-Pj - j) + Pi + i
    {
        for i in 0..n {
            tree.set(i, -ls[i] - i as isize);
        }

        for &i in order.iter().rev() {
            let f = tree.reduce(0, i) + ls[i] + i as isize;
            result[i] = result[i].min(f);
            tree.set(i, BIG_VALUE);
        }
    }

    let result = result
        .iter()
        .map(|v| v.to_string())
        .collect::<Vec<_>>()
        .join(" ");
    println!("{}", result);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc283/f/main.rs

%%%% begin
4
3 2 4 1
%%%%
2 2 3 3
%%%% end

%%%% begin
7
1 2 3 4 5 6 7
%%%%
2 2 2 2 2 2 2
%%%% end

%%%% begin
16
12 10 7 14 8 3 11 13 2 5 6 16 4 1 15 9
%%%%
3 3 3 5 3 4 3 3 4 2 2 4 4 4 4 7
%%%% end
*/

//
// segment tree for range minimum
//

type Value = isize;

fn value_id() -> Value {
    BIG_VALUE
}

fn value_multiply(lhs: Value, rhs: Value) -> Value {
    lhs.min(rhs)
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
