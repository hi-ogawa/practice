// AC

// https://atcoder.jp/contests/abc299/tasks/abc299_e

use std::collections::{BTreeSet, VecDeque};

fn main() {
    // n ~ 2000
    // m ~ 2000
    let (n, m) = {
        let v: Vec<usize> = read_tokens();
        (v[0], v[1])
    };

    let mut adj: Vec<Vec<usize>> = vec![vec![]; n];
    for _ in 0..m {
        let (u, v) = {
            let v: Vec<usize> = read_tokens();
            (v[0] - 1, v[1] - 1)
        };
        adj[u].push(v);
        adj[v].push(u);
    }

    let k: usize = read_tokens()[0];
    let mut constraints: Vec<(usize, usize)> = vec![];
    for _ in 0..k {
        let v: Vec<usize> = read_tokens();
        constraints.push((v[0] - 1, v[1]));
    }

    // distance by BFS
    let bfs = |root: usize| -> Vec<usize> {
        let mut dist: Vec<usize> = vec![std::usize::MAX; n];
        let mut queue: VecDeque<usize> = VecDeque::new();
        dist[root] = 0;
        queue.push_back(root);
        while let Some(v) = queue.pop_front() {
            for &u in &adj[v] {
                if dist[u] == std::usize::MAX {
                    dist[u] = dist[v] + 1;
                    queue.push_back(u);
                }
            }
        }
        dist
    };

    // construct constraints
    let mut all_white: BTreeSet<usize> = BTreeSet::new();
    let mut all_exist_black: Vec<Vec<usize>> = vec![vec![]; n];

    for &(p, d) in &constraints {
        let dist = bfs(p);
        for u in 0..n {
            if dist[u] == d {
                all_exist_black[p].push(u);
            }
            if dist[u] < d {
                all_white.insert(u);
            }
        }
    }

    // check constraints
    let mut colors: Vec<usize> = vec![1; n];
    for &i in &all_white {
        colors[i] = 0;
    }

    for &(p, _) in &constraints {
        if all_exist_black[p].iter().all(|i| colors[*i] == 0) {
            println!("No");
            return;
        }
    }

    println!("Yes");
    for i in 0..n {
        print!("{}", colors[i]);
    }
    println!();
}

/*
python misc/run.py atcoder/abc299/e/main.rs

%%%% begin
5 5
1 2
2 3
3 1
3 4
4 5
2
1 0
5 2
%%%%
Yes
10100
%%%% end

%%%% begin
5 5
1 2
2 3
3 1
3 4
4 5
5
1 1
2 1
3 1
4 1
5 1
%%%%
No
%%%% end

%%%% begin
1 0
0
%%%%
Yes
1
%%%% end
*/

//
// utils
//

#[allow(dead_code)]
fn read_tokens<T: std::str::FromStr>() -> Vec<T>
where
    <T as std::str::FromStr>::Err: std::fmt::Debug,
{
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).unwrap();
    line.split_whitespace()
        .map(|s| s.parse().unwrap())
        .collect()
}
