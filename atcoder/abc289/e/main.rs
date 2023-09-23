// TLE

// https://atcoder.jp/contests/abc289/tasks/abc289_e

use std::collections::{HashMap, VecDeque};

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

    // adjacency on product graph G x G
    let mut adj: HashMap<(usize, usize), Vec<(usize, usize)>> = HashMap::new();
    for &e in &edges {
        for &f in &edges {
            if ls[e.1] != ls[f.1] {
                adj.entry((e.0, f.0)).or_default().push((e.1, f.1));
            }
        }
    }

    // BFS for shortest path
    let mut visited: HashMap<(usize, usize), bool> = HashMap::new();
    let mut queue: VecDeque<((usize, usize), usize)> = VecDeque::new();
    let mut result: isize = -1;
    queue.push_back(((0, n - 1), 0));
    while let Some((v, d)) = queue.pop_front() {
        if visited.get(&v) == Some(&true) {
            continue;
        }
        if v == (n - 1, 0) {
            result = d as isize;
            break;
        }
        visited.insert(v, true);
        for &u in adj.get(&v).unwrap_or(&vec![]) {
            if visited.get(&u) == Some(&true) {
                continue;
            }
            queue.push_back((u, d + 1));
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
python misc/run.py atcoder/abc289/e/main.rs

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
