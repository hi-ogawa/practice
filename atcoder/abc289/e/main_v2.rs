// AC

// https://atcoder.jp/contests/abc289/tasks/abc289_e

use std::collections::VecDeque;

fn main_case() {
    // 2 <= n ~ 10^3
    // m ~ 10^3
    let (n, m) = {
        let v: Vec<usize> = read_tokens();
        (v[0], v[1])
    };
    let ls: Vec<usize> = read_tokens();

    let mut edges: Vec<(usize, usize)> = vec![];
    for _ in 0..m {
        let v: Vec<usize> = read_tokens();
        edges.push((v[0] - 1, v[1] - 1));
        edges.push((v[1] - 1, v[0] - 1));
    }

    let enc = |x: usize, y: usize| -> usize { x * n + y };

    // adjacency on product graph G x G
    let mut adj: Vec<Vec<usize>> = vec![vec![]; enc(n, n)];
    for &e in &edges {
        for &f in &edges {
            if ls[e.1] != ls[f.1] {
                adj[enc(e.0, f.0)].push(enc(e.1, f.1));
            }
        }
    }

    // BFS for shortest path
    let mut queued: Vec<bool> = vec![false; enc(n, n)];
    let mut queue: VecDeque<(usize, usize)> = VecDeque::new();
    let mut result: isize = -1;
    queue.push_back((enc(0, n - 1), 0));
    queued[enc(0, n - 1)] = true;
    while let Some((v, d)) = queue.pop_front() {
        if v == enc(n - 1, 0) {
            result = d as isize;
            break;
        }
        for &u in &adj[v] {
            if queued[u] {
                continue;
            }
            queue.push_back((u, d + 1));
            queued[u] = true;
        }
    }

    println!("{}", result);
}

fn main() {
    let t: usize = read_tokens()[0];
    for _ in 0..t {
        main_case();
    }
}

/*
python misc/run.py atcoder/abc289/e/main_v2.rs

%%%% begin
3
4 4
0 1 0 1
1 2
2 3
1 3
2 4
3 3
0 1 0
1 2
2 3
1 3
6 6
0 0 1 1 0 1
1 2
2 6
3 6
4 6
4 5
2 4
%%%%
3
-1
3
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
