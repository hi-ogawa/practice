// AC

// https://atcoder.jp/contests/abc282/tasks/abc282_d

use std::{
    collections::{HashMap, VecDeque},
    fmt::Debug,
    io,
    str::FromStr,
};

fn main_case() -> io::Result<()> {
    // ~ 10^5
    let (n, m) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;

    let mut adj: Vec<Vec<usize>> = vec![vec![]; n];
    for _ in 0..m {
        let e: Vec<usize> = read_tokens()?;
        adj[e[0] - 1].push(e[1] - 1);
        adj[e[1] - 1].push(e[0] - 1);
    }

    //
    // PROP.
    //   answer = (∑_v |V| - |V_bip(v)| - |V_adj(v)|) / 2
    //                    ^^^^^^^^^^^^^^^^^^^^^^^^^^
    //                    only connecting to these vertices would break the condition
    //   where
    //     V_adj(v) = { vertices adjacent to v }
    //     V_bip(v) = { vertices which are in the same bipartite parity as v }
    //

    // BFS to compute connected components and bipartite parity

    // 0: uninitialized
    // 1, -1: bipartite parity of 1st component
    // 1, -2:       ...       of 2nd component
    // ...
    let mut parity: Vec<isize> = vec![0; n];

    let mut solve_bipartite = || -> bool {
        let mut num_components = 0;

        for root in 0..n {
            if parity[root] != 0 {
                continue;
            }
            num_components += 1;

            let mut queue: VecDeque<usize> = VecDeque::new();
            queue.push_back(root);
            parity[root] = num_components;

            while let Some(v) = queue.pop_front() {
                for &u in &adj[v] {
                    if parity[u] == 0 {
                        parity[u] = -parity[v];
                        queue.push_back(u);
                        continue;
                    }
                    if parity[u] == parity[v] {
                        return false;
                    }
                    if parity[u] == -parity[v] {
                        continue;
                    }
                    unreachable!();
                }
            }
        }
        true
    };

    let is_bipartite = solve_bipartite();

    if !is_bipartite {
        println!("0");
        return Ok(());
    }

    let mut parity_counts: HashMap<isize, usize> = HashMap::new();
    for v in 0..n {
        assert!(parity[v] != 0);
        *parity_counts.entry(parity[v]).or_default() += 1;
    }

    let result = (0..n)
        .map(|v| n - parity_counts[&parity[v]] - adj[v].len())
        .sum::<usize>()
        / 2;
    println!("{}", result);

    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc282/d/main.rs

%%%% begin
5 4
4 2
3 1
5 2
3 2
%%%%
2
%%%% end

%%%% begin
4 3
3 1
3 2
1 2
%%%%
0
%%%% end

%%%% begin
9 11
4 9
9 1
8 2
8 3
9 2
8 4
6 7
4 6
7 5
4 5
7 8
%%%%
9
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
