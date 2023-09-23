// AC

// https://atcoder.jp/contests/abc289/tasks/abc289_d

use std::collections::HashSet;

fn main() {
    // n ~ 10
    let _n: usize = read_tokens()[0];
    let ls1: Vec<usize> = read_tokens();

    // m ~ 10^5
    let _m: usize = read_tokens()[0];
    let ls2: Vec<usize> = read_tokens();
    let ls2: HashSet<usize> = ls2.iter().copied().collect();

    let x: usize = read_tokens()[0];

    // dp[i] = ...
    let mut dp: Vec<bool> = vec![false; x + 1];
    dp[0] = true;

    for i in 1..=x {
        if ls2.contains(&i) {
            continue;
        }
        for &a in &ls1 {
            if a <= i {
                dp[i] = dp[i] || dp[i - a];
            }
        }
    }

    let result = if dp[x] { "Yes" } else { "No" };
    println!("{}", result);
}

/*
python misc/run.py atcoder/abc289/d/main.rs

%%%% begin
3
3 4 5
4
4 5 6 8
15
%%%%
Yes
%%%% end

%%%% begin
4
2 3 4 5
4
3 4 5 6
8
%%%%
No
%%%% end

%%%% begin
4
2 5 7 8
5
2 9 10 11 19
20
%%%%
Yes
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
