// AC

// https://atcoder.jp/contests/abc291/tasks/abc291_e

fn main() {
    // ~ 10^5
    let (n, m) = {
        let v: Vec<usize> = read_tokens();
        (v[0], v[1])
    };

    // WLOG, add dummy node "0" for algorithmic simplicity

    let mut adj: Vec<Vec<usize>> = vec![vec![]; n + 1];
    for _ in 0..m {
        let v: Vec<usize> = read_tokens();
        adj[v[0]].push(v[1]);
    }
    for v in 1..=n {
        adj[0].push(v);
    }

    let mut in_degrees: Vec<usize> = vec![0; n + 1];
    for dests in &adj {
        for &v in dests {
            in_degrees[v] += 1;
        }
    }

    // PROP. greedily solvable via BFS  \iff  DAG has unique topological sort

    let mut zeros: Vec<usize> = vec![0];
    let mut result: Vec<usize> = vec![0; n + 1];

    let mut solve = || -> bool {
        for x in 0..=n {
            // pick candidate
            if zeros.len() != 1 {
                return false;
            }
            let v = zeros[0];
            result[v] = x;
            zeros.clear();

            // BFS
            for &u in &adj[v] {
                assert!(in_degrees[u] > 0);
                in_degrees[u] -= 1;
                if in_degrees[u] == 0 {
                    zeros.push(u);
                }
            }
        }
        true
    };

    let ok = solve();
    println!("{}", if ok { "Yes" } else { "No" });
    if ok {
        println!(
            "{}",
            result[1..]
                .iter()
                .map(|x| x.to_string())
                .collect::<Vec<_>>()
                .join(" ")
        );
    }
}

/*
python misc/run.py atcoder/abc291/e/main_v2.rs

%%%% begin
3 2
3 1
2 3
%%%%
Yes
3 1 2
%%%% end

%%%% begin
3 2
3 1
3 2
%%%%
No
%%%% end

%%%% begin
4 6
1 2
1 2
2 3
2 3
3 4
3 4
%%%%
Yes
1 2 3 4
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
