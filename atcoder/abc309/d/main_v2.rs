// AC

// https://atcoder.jp/contests/abc309/tasks/abc309_d

use std::collections::VecDeque;

fn main() {
    let [n1, n2, m] = read_array::<usize, 3>();
    let n = n1 + n2;
    let mut adj: Vec<Vec<usize>> = vec![vec![]; n];
    for _ in 0..m {
        let [u, v] = read_array::<usize, 2>();
        adj[u - 1].push(v - 1);
        adj[v - 1].push(u - 1);
    }

    // BFS to compute distance within each component
    let mut distance: Vec<Option<usize>> = vec![None; n];

    let mut bfs = |root: usize| {
        let mut queue: VecDeque<usize> = VecDeque::new();
        queue.push_back(root);
        distance[root] = Some(0);
        while let Some(v) = queue.pop_front() {
            for &u in &adj[v] {
                if distance[u].is_none() {
                    distance[u] = Some(distance[v].unwrap() + 1);
                    queue.push_back(u);
                }
            }
        }
    };

    bfs(0);
    bfs(n - 1);
    let d1 = (0..n1).flat_map(|i| distance[i]).max().unwrap();
    let d2 = (n1..n).flat_map(|i| distance[i]).max().unwrap();
    println!("{}", d1 + d2 + 1);
}

/*
python misc/run.py atcoder/abc309/d/main.rs

%%%% begin
3 4 6
1 2
2 3
4 5
4 6
1 3
6 7
%%%%
5
%%%% end

%%%% begin
7 5 20
10 11
4 5
10 12
1 2
1 5
5 6
2 4
3 5
9 10
2 5
1 4
11 12
9 12
8 9
5 7
3 7
3 6
3 4
8 12
9 11
%%%%
4
%%%% end
*/

//
// utils
//

#[allow(dead_code)]
fn read_vec<T: std::str::FromStr>() -> Vec<T> {
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).unwrap();
    line.split_whitespace()
        .map(|s| s.parse().ok().unwrap())
        .collect()
}

#[allow(dead_code)]
fn read_array<T: std::str::FromStr, const LEN: usize>() -> [T; LEN] {
    #[allow(unused_imports)]
    use std::convert::TryInto;
    read_vec::<T>().try_into().ok().unwrap()
}
