// AC

// https://atcoder.jp/contests/abc305/tasks/abc305_e

fn main() {
    // ~ 10^5
    let v: Vec<usize> = read_tokens();
    let (n, m, k) = (v[0], v[1], v[2]);

    let mut adj: Vec<Vec<usize>> = vec![vec![]; n];
    for _ in 0..m {
        let v: Vec<usize> = read_tokens();
        adj[v[0] - 1].push(v[1] - 1);
        adj[v[1] - 1].push(v[0] - 1);
    }

    let mut guards: Vec<Vec<usize>> = vec![vec![]; n + 1];
    for _ in 0..k {
        let v: Vec<usize> = read_tokens();
        guards[v[1]].push(v[0] - 1);
    }

    // solve from top
    let mut visited: Vec<bool> = vec![false; n];
    let mut curr: Vec<usize> = vec![];
    let mut next: Vec<usize> = vec![];
    for h in (1..=n).rev() {
        // add guard
        for &v in &guards[h] {
            if !visited[v] {
                visited[v] = true;
                curr.push(v);
            }
        }
        // move one hop
        for &v in &curr {
            for &u in &adj[v] {
                if !visited[u] {
                    visited[u] = true;
                    next.push(u);
                }
            }
        }
        curr.clear();
        curr.append(&mut next);
        curr.sort();
        curr.dedup();
    }

    let result: Vec<usize> = (0..n).filter(|&i| visited[i]).collect();
    println!(
        "{}\n{}",
        result.len(),
        result
            .iter()
            .map(|x| (x + 1).to_string())
            .collect::<Vec<_>>()
            .join(" ")
    );
}

/*
python misc/run.py atcoder/abc305/e/main.rs

%%%% begin
5 5 2
1 2
2 3
2 4
3 5
1 5
1 1
5 2
%%%%
4
1 2 3 5
%%%% end

%%%% begin
3 0 1
2 3
%%%%
1
2
%%%% end

%%%% begin
10 10 2
2 1
5 1
6 1
2 4
2 5
2 10
8 5
8 6
9 6
7 9
3 4
8 2
%%%%
7
1 2 3 5 6 8 9
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
