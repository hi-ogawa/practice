// AC

// https://atcoder.jp/contests/abc302/tasks/abc302_e

use std::collections::BTreeSet;

fn main() {
    let v: Vec<usize> = read_tokens();
    let (n, nq) = (v[0], v[1]); // ~ 10^5

    let mut adj: Vec<BTreeSet<usize>> = vec![BTreeSet::new(); n + 1];

    // compute incrementally
    let mut result = n;

    for _ in 0..nq {
        let q: Vec<String> = read_tokens();
        match q[0].as_str() {
            "1" => {
                let [u, v]: [usize; 2] = [q[1].parse().unwrap(), q[2].parse().unwrap()];
                adj[u].insert(v);
                adj[v].insert(u);
                if adj[u].len() == 1 {
                    result -= 1;
                }
                if adj[v].len() == 1 {
                    result -= 1;
                }
            }
            "2" => {
                let v: usize = q[1].parse().unwrap();
                // loop at most "nq" in total
                for u in adj[v].clone() {
                    if adj[u].len() == 1 {
                        result += 1;
                    }
                    adj[u].remove(&v);
                }
                if adj[v].len() > 0 {
                    result += 1;
                }
                adj[v].clear();
            }
            _ => unreachable!(),
        }
        println!("{}", result);
    }
}

/*
python misc/run.py atcoder/abc302/e/main.rs

%%%% begin
3 7
1 1 2
1 1 3
1 2 3
2 1
1 1 2
2 2
1 1 2
%%%%
1
0
0
1
0
3
1
%%%% end

%%%% begin
2 1
2 1
%%%%
2
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
