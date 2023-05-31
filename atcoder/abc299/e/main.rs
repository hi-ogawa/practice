// WIP

// https://atcoder.jp/contests/abc299/tasks/abc299_e

use std::collections::BTreeSet;

fn main() {
    // n ~ 2000
    let (n, m) = {
        let v: Vec<usize> = read_tokens();
        (v[0], v[1])
    };

    let mut adj: Vec<Vec<bool>> = vec![vec![false; n]; n];
    for _ in 0..m {
        let (u, v) = {
            let v: Vec<usize> = read_tokens();
            (v[0] - 1, v[1] - 1)
        };
        adj[u][v] = true;
        adj[v][u] = true;
    }

    // distance between all pairs
    let mut dist: Vec<Vec<usize>> = vec![vec![std::usize::MAX; n]; n];
    // for i in 0..n {
    //     dist[i][i] = 0;
    // }
    // for u in 0..n {
    //     for v in 0..n {
    //         if adj[u][v] {
    //             dist[u][v] = 1;
    //         }
    //     }
    // }
    // for k in 0..n {
    //     for u in 0..n {
    //         for v in 0..n {
    //             dist[u][v] = std::cmp::min(dist[u][v], dist[u][k] + dist[k][v]);
    //         }
    //     }
    // }

    // collect constraints
    let k: usize = read_tokens()[0];
    let mut all_white: BTreeSet<usize> = BTreeSet::new();
    let mut all_exist_black: Vec<Vec<usize>> = vec![vec![]; k];

    for i in 0..k {
        let (p, d) = {
            let v: Vec<usize> = read_tokens();
            (v[0] - 1, v[1])
        };
        for u in 0..n {
            if dist[p][u] == d {
                all_exist_black[i].push(u);
            }
            if dist[p][u] < d {
                all_white.insert(u);
            }
        }
    }

    // check constraints
    let mut colors: Vec<usize> = vec![0; n];
    for &i in &all_white {
        colors[i] = 1;
    }

    for exist_black in &all_exist_black {
        if exist_black.iter().all(|i| colors[*i] == 1) {
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
