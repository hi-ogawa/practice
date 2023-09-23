// AC

// https://atcoder.jp/contests/abc291/tasks/abc291_e

fn main() {
    // ~ 10^5
    let (n, m) = {
        let v: Vec<usize> = read_tokens();
        (v[0], v[1])
    };

    let mut adj: Vec<Vec<usize>> = vec![vec![]; n];
    for _ in 0..m {
        let v: Vec<usize> = read_tokens();
        adj[v[0] - 1].push(v[1] - 1);
    }

    // PROP. greedily solvable via BFS  \iff  DAG has unique topological sort

    let mut in_degrees: Vec<usize> = vec![0; n];
    let mut zeros: Vec<usize> = vec![];

    for edges in &adj {
        for &i in edges {
            in_degrees[i] += 1;
        }
    }

    for i in 0..n {
        if in_degrees[i] == 0 {
            zeros.push(i);
        }
    }

    let mut result: Vec<usize> = vec![0; n];

    let mut solve = || -> bool {
        for x in 1..=n {
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
            result
                .iter()
                .map(|x| x.to_string())
                .collect::<Vec<_>>()
                .join(" ")
        );
    }
}

/*
python misc/run.py atcoder/abc291/e/main.rs

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
