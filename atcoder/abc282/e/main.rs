// AC

// https://atcoder.jp/contests/abc282/tasks/abc282_e

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // n ~ 500
    // m ~ 10^9
    let (n, m) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;
    // a ~ 10^9
    let ls: Vec<usize> = read_tokens()?;

    // precompute f(x, y) = (x^y + y^x) % m
    let mut edges: Vec<(usize, usize, usize)> = vec![];
    for i in 0..n {
        for j in 0..i {
            let x = ls[i];
            let y = ls[j];
            let f = (pow_mod(x, y, m) + pow_mod(y, x, m)) % m;
            edges.push((i, j, f));
        }
    }
    edges.sort_by_key(|&(_, _, f)| -(f as isize));

    // solve maximum spanning tree (sort edges and greedily connect)
    let mut dsu = Dsu::new(n);
    let mut result: usize = 0;
    for &(i, j, f) in &edges {
        if dsu.find(i) != dsu.find(j) {
            dsu.merge(i, j);
            result += f;
        }
    }
    println!("{}", result);

    Ok(())
}

//
// dsu
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
// x^y % m
//

fn pow_mod(mut x: usize, mut y: usize, m: usize) -> usize {
    let mut z = 1;
    while y > 0 {
        if y & 1 == 1 {
            z = (z * x) % m;
        }
        x = (x * x) % m;
        y >>= 1;
    }
    z
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc282/e/main.rs

%%%% begin
4 10
4 2 3 2
%%%%
20
%%%% end

%%%% begin
20 100
29 31 68 20 83 66 23 84 69 96 41 61 83 37 52 71 18 55 40 8
%%%%
1733
%%%% end
*/

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
    for token in line.trim().split(" ") {
        let value: F = token
            .parse()
            .map_err(|e| io::Error::new(io::ErrorKind::Other, format!("{:?}", e)))?;
        result.push(value);
    }
    Ok(result)
}
