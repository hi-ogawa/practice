// AC

// https://atcoder.jp/contests/abc266/tasks/abc266_f

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let n = read_tokens::<usize>()?[0]; // [3, 2 x 10^5]

    let mut adj: Vec<Vec<usize>> = vec![vec![]; n];
    for _ in 0..n {
        let e: Vec<usize> = read_tokens()?;
        let (x, y) = (e[0] - 1, e[1] - 1);
        adj[x].push(y);
        adj[y].push(x);
    }

    //
    // dfs to find unique back edge
    //

    struct Dfs<'a> {
        adj: &'a Vec<Vec<usize>>,
        done: Vec<bool>,
        parents: Vec<usize>,
        back_edges: Vec<(usize, usize)>,
    }

    impl Dfs<'_> {
        fn run(&mut self, x: usize) {
            self.done[x] = true;
            for &y in &self.adj[x] {
                if self.done[y] {
                    if y != self.parents[x] {
                        self.back_edges.push((x, y));
                    }
                    continue;
                }
                self.parents[y] = x;
                self.run(y);
            }
        }
    }

    let mut dfs = Dfs {
        adj: &adj,
        done: vec![false; n],
        parents: vec![std::usize::MAX; n],
        back_edges: vec![],
    };
    dfs.run(0);

    //
    // find loop paths
    //
    assert!(dfs.back_edges.len() == 2);
    let (c, p) = dfs.back_edges[0];
    let mut in_loop: Vec<bool> = vec![false; n]; // path([c, p])
    {
        let mut x = c;
        while x != p {
            in_loop[x] = true;
            x = dfs.parents[x];
        }
        in_loop[p] = true;
    }

    //
    // find components in the graph when all loop edges are removed (TODO: simple dfs is enough)
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

        fn merge(&mut self, mut x: usize, mut y: usize) {
            x = self.find(x);
            y = self.find(y);
            self.parents[x] = y;
        }
    }

    let mut dsu = Dsu::new(n);
    for x in 0..n {
        for &y in &adj[x] {
            if !(in_loop[x] && in_loop[y]) {
                dsu.merge(x, y);
            }
        }
    }

    // no loop in the simple path if two belong to the same component
    let mut solve = |x: usize, y: usize| -> bool { dsu.find(x) == dsu.find(y) };

    //
    // answer queries
    //
    let nq = read_tokens::<usize>()?[0];
    for _ in 0..nq {
        let e: Vec<usize> = read_tokens()?;
        if solve(e[0] - 1, e[1] - 1) {
            println!("Yes");
        } else {
            println!("No");
        }
    }
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc266/f/main.rs

%%%% begin
5
1 2
2 3
1 3
1 4
2 5
3
1 2
1 4
1 5
%%%%
No
Yes
No
%%%% end

%%%% begin
10
3 5
5 7
4 8
2 9
1 2
7 9
1 6
4 10
2 5
2 10
10
1 8
6 9
8 10
6 8
3 10
3 9
1 10
5 8
1 10
7 8
%%%%
Yes
No
Yes
Yes
No
No
Yes
No
Yes
No
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
