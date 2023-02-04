// AC

// https://atcoder.jp/contests/abc280/tasks/abc280_f

use std::{collections::VecDeque, fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let (n, m, q) = read_tokens::<usize>().map(|v| (v[0], v[1], v[2]))?;

    let mut adj: Vec<Vec<(usize, isize)>> = vec![vec![]; n];
    for _ in 0..m {
        let (a, b, c) =
            read_tokens::<isize>().map(|v| (v[0] as usize - 1, v[1] as usize - 1, v[2]))?;
        adj[a].push((b, c));
        adj[b].push((a, -c));
    }

    // PROP. 1
    //   each connected component is strongly-connected

    // PROP. 2
    //    there exists "inf" score cycle
    //      \iff
    //    there exists "-inf" score cycle

    // PROP. 3
    //    there's no "inf" score cycle
    //      \iff
    //    all cycles have "zero" score
    //      \iff
    //    given two vertices, all paths between two have a same score

    // compute connected components
    let mut dsu = Dsu::new(n);
    for x in 0..n {
        for &(y, _) in &adj[x] {
            dsu.merge(x, y);
        }
    }

    // BFS to compute path scores and check if it's "well-defined" (otherwise "inf" cycle exists)
    let mut is_inf: Vec<bool> = vec![false; n];
    const NO_VALUE: isize = std::isize::MAX;
    let mut scores: Vec<isize> = vec![NO_VALUE; n]; // well-defined scroe from each components' root

    for x in 0..n {
        let root = dsu.find(x);
        if root != x {
            continue;
        }

        let mut bfs = || -> bool {
            let mut queue: VecDeque<usize> = VecDeque::new();
            queue.push_back(root);
            scores[root] = 0;

            while let Some(a) = queue.pop_front() {
                for &(b, c) in &adj[a] {
                    if scores[b] == NO_VALUE {
                        scores[b] = scores[a] + c;
                        queue.push_back(b);
                        continue;
                    }
                    if scores[b] != scores[a] + c {
                        return true;
                    }
                }
            }
            return false;
        };
        is_inf[root] = bfs();
    }

    // answer queries
    for _ in 0..q {
        let (x, y) = read_tokens::<usize>().map(|v| (v[0] - 1, v[1] - 1))?;
        if dsu.find(x) != dsu.find(y) {
            println!("nan");
            continue;
        }
        let root = dsu.find(x);
        if is_inf[root] {
            println!("inf");
            continue;
        }
        let result = -scores[x] + scores[y];
        println!("{}", result);
    }

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
        Dsu {
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
python misc/run.py atcoder/abc280/f/main.rs

%%%% begin
5 5 3
1 2 1
1 2 2
3 4 1
4 5 1
3 5 2
5 3
1 2
3 1
%%%%
-2
inf
nan
%%%% end

%%%% begin
2 1 1
1 1 1
1 1
%%%%
inf
%%%% end

%%%% begin
9 7 5
3 1 4
1 5 9
2 6 5
3 5 8
9 7 9
3 2 3
8 4 6
2 6
4 3
3 8
3 2
7 9
%%%%
inf
nan
nan
inf
-9
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
    for token in line.trim().split(' ') {
        let value: F = token
            .parse()
            .map_err(|e| io::Error::new(io::ErrorKind::Other, format!("{:?}", e)))?;
        result.push(value);
    }
    Ok(result)
}
