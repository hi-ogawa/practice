// AC

// https://atcoder.jp/contests/abc277/tasks/abc277_e

use std::{collections::BTreeSet, fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // define a new weighted graph G = (V, e)
    //   V = { x_1, y_1, x_2, y_2, ... }
    //   E = { (x_i, x_j, 1) | (i, j) \in E0 } ∪
    //       { (y_i, y_j, 1) | (i, j) \in E1 } ∪
    //       { (x_i, y_i, 0) | i \in S }
    // the idea is
    //   - two layers of vertices
    //   - old edges E0 and E1 lives in each layer (with distance one)
    //   - switch connecting vertices from one layer to another (with distance zero)

    let (n, m, k) = read_tokens::<usize>().map(|v| (v[0], v[1], v[2]))?;

    //
    // construct graph
    //
    let num_verts = 2 * n;
    let mut adj: Vec<Vec<(usize, usize)>> = vec![vec![]; num_verts];
    for _ in 0..m {
        let (mut u, mut v, a) = read_tokens::<usize>().map(|v| (v[0] - 1, v[1] - 1, v[2]))?;
        if a == 0 {
            u += n;
            v += n;
        }
        adj[u].push((v, 1));
        adj[v].push((u, 1));
    }

    // is k = 0 possible?
    if k > 0 {
        let switches: Vec<usize> = read_tokens()?;
        for s in switches {
            let s = s - 1;
            adj[s].push((s + n, 0));
            adj[s + n].push((s, 0));
        }
    }

    //
    // solve dijkstra/bfs
    //
    let mut queue: BTreeSet<(usize, usize)> = BTreeSet::new(); // (distance, vertex)
    let mut distances: Vec<usize> = vec![std::usize::MAX; num_verts];

    queue.insert((0, 0));
    while let Some((d, v)) = pop_first(&mut queue) {
        distances[v] = d;
        for &(u, w) in &adj[v] {
            if d + w < distances[u] {
                queue.remove(&(distances[u], u));
                distances[u] = d + w;
                queue.insert((d + w, u));
            }
        }
    }

    let result = distances[n - 1].min(distances[2 * n - 1]);
    if result == std::usize::MAX {
        println!("-1");
    } else {
        println!("{}", result);
    }
    Ok(())
}

fn pop_first(queue: &mut BTreeSet<(usize, usize)>) -> Option<(usize, usize)> {
    if let Some(&e) = queue.iter().next() {
        queue.remove(&e);
        Some(e)
    } else {
        None
    }
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc277/e/main.rs

%%%% begin
5 5 2
1 3 0
2 3 1
5 4 1
2 1 1
1 4 0
3 4
%%%%
5
%%%% end

%%%% begin
4 4 2
4 3 0
1 2 1
1 2 0
2 1 1
2 4
%%%%
-1
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
