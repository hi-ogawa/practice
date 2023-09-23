// AC

// https://atcoder.jp/contests/abc303/tasks/abc303_e

use std::collections::BTreeSet;

fn main() {
    // ~ 10^5
    let n: usize = read_tokens()[0];

    let mut adj: Vec<BTreeSet<usize>> = vec![BTreeSet::new(); n];
    for _ in 0..(n - 1) {
        let v: Vec<usize> = read_tokens();
        adj[v[0] - 1].insert(v[1] - 1);
        adj[v[1] - 1].insert(v[0] - 1);
    }

    // loop by
    //  1. collect tree leaves
    //  2. collect parants of leaves
    //  3. remove such parents as "star centers"

    let mut leaves: Vec<usize> = (0..n).filter(|&i| adj[i].len() == 1).collect();
    let mut star_sizes: Vec<usize> = vec![];

    while !leaves.is_empty() {
        // collect centers
        let mut star_centers: BTreeSet<usize> = BTreeSet::new();
        for &v in &leaves {
            for &u in &adj[v] {
                star_centers.insert(u);
            }
        }
        for &u in &star_centers {
            star_sizes.push(adj[u].len());
        }

        // remove star leaves
        let mut to_remove: Vec<(usize, usize)> = vec![];
        for &c in &star_centers {
            for &l in &adj[c] {
                for &u in &adj[l] {
                    to_remove.push((l, u));
                }
            }
        }
        for &(l, u) in &to_remove {
            adj[l].remove(&u);
            adj[u].remove(&l);
        }

        // find next tree leaves
        leaves.clear();
        for &(_, u) in &to_remove {
            // 0 or 1 (0 if u is in to_remove)
            if adj[u].len() == 1 {
                leaves.push(u);
            }
        }
    }

    star_sizes.sort();
    println!(
        "{}",
        star_sizes
            .iter()
            .map(|v| v.to_string())
            .collect::<Vec<String>>()
            .join(" ")
    );
}

/*
python misc/run.py atcoder/abc303/e/main.rs

%%%% begin
6
1 2
2 3
3 4
4 5
5 6
%%%%
2 2
%%%% end

%%%% begin
9
3 9
7 8
8 6
4 6
4 1
5 9
7 3
5 2
%%%%
2 2 2
%%%% end

%%%% begin
20
8 3
8 18
2 19
8 20
9 17
19 7
8 7
14 12
2 15
14 10
2 13
2 16
2 1
9 5
10 15
14 6
2 4
2 11
5 12
%%%%
2 3 4 7
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
