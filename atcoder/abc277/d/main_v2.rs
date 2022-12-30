// AC

// https://atcoder.jp/contests/abc277/tasks/abc277_d

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // n ~ 10^5
    // m ~ [2, 10^9]
    let (n, m) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;

    // x \in [0, m)
    let mut ls: Vec<usize> = read_tokens()?;
    ls.sort(); // WLOG, already orderded

    //
    // compute connected components
    //

    let mut dsu = Dsu::new(n);

    for i in 0..(n - 1) {
        if ls[i + 1] == ls[i] || ls[i + 1] == ls[i] + 1 {
            dsu.merge(i + 1, i);
        }
    }

    if ls[0] == 0 && ls[n - 1] == m - 1 {
        dsu.merge(0, n - 1);
    }

    //
    // take maximum of sums
    //
    let mut sums: Vec<usize> = vec![0; n];
    for i in 0..n {
        sums[dsu.find(i)] += ls[i];
    }

    let result = ls.iter().sum::<usize>() - sums.iter().max().unwrap();
    println!("{}", result);
    Ok(())
}

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

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc277/d/main_v2.rs

%%%% begin
9 7
3 0 2 5 5 3 0 6 3
%%%%
11
%%%% end

%%%% begin
1 10
4
%%%%
0
%%%% end

%%%% begin
20 20
18 16 15 9 8 8 17 1 3 17 11 9 12 11 7 3 2 14 3 12
%%%%
99
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
