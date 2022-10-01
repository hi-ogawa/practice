// AC

// https://atcoder.jp/contests/abc270/tasks/abc270_c

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let (n, x, y) = read_tokens::<usize>().map(|v| (v[0], v[1] - 1, v[2] - 1))?;
    let mut adj: Vec<Vec<usize>> = vec![vec![]; n];
    for _ in 0..(n - 1) {
        let (u, v) = read_tokens::<usize>().map(|v| (v[0] - 1, v[1] - 1))?;
        adj[u].push(v);
        adj[v].push(u);
    }

    // semi-DFS from x
    let mut parents: Vec<usize> = (0..n).collect();
    let mut visited: Vec<bool> = vec![false; n];
    let mut stack: Vec<usize> = vec![];
    stack.push(x);
    visited[x] = true;
    while let Some(u) = stack.pop() {
        for &v in &adj[u] {
            if visited[v] {
                continue;
            }
            stack.push(v);
            visited[v] = true;
            parents[v] = u;
        }
    }

    // follow back from y
    let mut path: Vec<usize> = vec![y];
    let mut z = y;
    while z != x {
        z = parents[z];
        path.push(z);
    }

    // print
    println!(
        "{}",
        path.iter()
            .rev()
            .map(|v| (v + 1).to_string())
            .collect::<Vec<_>>()
            .join(" ")
    );

    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc270/c/main.rs

%%%% begin
5 2 5
1 2
1 3
3 4
3 5
%%%%
2 1 3 5
%%%% end

%%%% begin
6 1 2
3 1
2 5
1 2
4 1
2 6
%%%%
1 2
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
