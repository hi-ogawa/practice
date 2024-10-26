// AC

// https://atcoder.jp/contests/abc376/tasks/abc376_d

use std::collections::VecDeque;

fn main() {
    let [n, m]: [usize; 2] = read_array();

    let mut adj: Vec<Vec<usize>> = vec![vec![]; n];
    for _ in 0..m {
        let [x, y]: [usize; 2] = read_array();
        adj[x - 1].push(y - 1);
    }

    // BFS
    let mut queue: VecDeque<(usize, usize)> = VecDeque::new();
    let mut visited: Vec<bool> = vec![false; n];
    queue.push_back((0, 0));
    visited[0] = true;

    while let Some((x, depth)) = queue.pop_front() {
        for &y in &adj[x] {
            if y == 0 {
                println!("{}", depth + 1);
                return;
            }
            if !visited[y] {
                queue.push_back((y, depth + 1));
                visited[y] = true;
            }
        }
    }
    println!("-1");
}

/*
python misc/run.py atcoder/abc376/d/main.rs

%%%% begin
3 3
1 2
2 3
3 1
%%%%
3
%%%% end

%%%% begin
3 2
1 2
2 3
%%%%
-1
%%%% end

%%%% begin
6 9
6 1
1 5
2 6
2 1
3 6
4 2
6 4
3 5
5 4
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
