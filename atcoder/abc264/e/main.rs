// AC

use std::{fmt::Debug, io, str::FromStr};

//
// DSU with component size
//

struct Dsu {
    parents: Vec<usize>,
    sizes: Vec<usize>,
}

impl Dsu {
    fn new(n: usize) -> Self {
        Dsu {
            parents: (0..n).collect(),
            sizes: vec![1; n],
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

    fn merge(&mut self, mut src: usize, mut dst: usize) {
        src = self.find(src);
        dst = self.find(dst);
        if src != dst {
            self.parents[src] = dst;
            self.sizes[dst] += self.sizes[src];
        }
    }
}

//
// main
//

fn main_case() -> io::Result<()> {
    let (n, _, e) = read_tokens::<usize>().map(|v| (v[0], v[1], v[2]))?; // [1, 5 x 10^5]

    // WLOG, all plants are connected and thus considered to be a single vertex "n"
    let normalize_vertex = |x: usize| x.min(n);

    let mut edges: Vec<(usize, usize)> = vec![];
    for _ in 0..e {
        let v: Vec<usize> = read_tokens()?;
        edges.push((normalize_vertex(v[0] - 1), normalize_vertex(v[1] - 1)));
    }

    let nq: usize = read_tokens()?[0];
    let mut qs: Vec<usize> = vec![];
    for _ in 0..nq {
        let v: usize = read_tokens()?[0];
        qs.push(v - 1);
    }

    //
    // simulate backward
    //

    let mut dsu = Dsu::new(n + 1);
    let mut results: Vec<usize> = vec![];
    let mut current = 0;

    let mut add_edge = |i: usize| -> usize {
        let (mut x, mut y) = edges[i];
        x = dsu.find(x);
        y = dsu.find(y);
        match (x == n, y == n) {
            (false, false) => {
                dsu.merge(x, y);
                0
            }
            (false, true) => {
                let size = dsu.sizes[x];
                dsu.merge(x, n);
                size
            }
            (true, false) => {
                let size = dsu.sizes[y];
                dsu.merge(y, n);
                size
            }
            (true, true) => 0,
        }
    };

    // final edges
    let mut last = vec![true; e];
    for &i in &qs {
        last[i] = false;
    }
    for i in 0..e {
        if last[i] {
            current += add_edge(i);
        }
    }

    // add edges
    for &i in qs.iter().rev() {
        results.push(current);
        current += add_edge(i);
    }

    for result in results.iter().rev() {
        println!("{}", result);
    }

    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc264/e/main.rs

%%%% begin
5 5 10
2 3
4 10
5 10
6 9
2 9
4 8
1 7
3 6
8 10
1 8
6
3
5
8
10
2
7
%%%%
4
4
2
2
2
1
%%%% end
*/

//
// utils
//

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
