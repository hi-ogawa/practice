// AC

// https://atcoder.jp/contests/abc292/tasks/abc292_e

use std::collections::VecDeque;

fn main() {
    // ~ 10^3
    let (n, m) = {
        let v: Vec<usize> = read_tokens();
        (v[0], v[1])
    };

    // directed
    let mut adj: Vec<Vec<usize>> = vec![vec![]; n];
    for _ in 0..m {
        let v: Vec<usize> = read_tokens();
        adj[v[0] - 1].push(v[1] - 1);
    }

    // PROP.
    //   x --> y is reachable => direct edger from x to y

    // BFS from each vertex to count reachable
    // (it can be solved based on topological sort of DAG of strong connected components, but here we can do simpler brute force since n and m are small.)

    let bfs = |root: usize| -> usize {
        let mut visited = vec![false; n];
        let mut queue: VecDeque<usize> = VecDeque::new();
        visited[root] = true;
        queue.push_back(root);
        while let Some(x) = queue.pop_front() {
            for &y in &adj[x] {
                if !visited[y] {
                    visited[y] = true;
                    queue.push_back(y);
                }
            }
        }
        visited.iter().filter(|&&v| v).count()
    };

    let total: usize = (0..n).map(bfs).sum();
    let result = total - n - m;
    println!("{}", result);
}

/*
python misc/run.py atcoder/abc292/e/main.rs

%%%% begin
4 3
2 4
3 1
4 3
%%%%
3
%%%% end

%%%% begin
292 0
%%%%
0
%%%% end

%%%% begin
5 8
1 2
2 1
1 3
3 1
1 4
4 1
1 5
5 1
%%%%
12
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
