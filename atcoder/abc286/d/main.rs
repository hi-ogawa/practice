// WIP

// https://atcoder.jp/contests/abc286/tasks/abc286_d

fn main() {
    // n ~ 10^2
    // x ~ 10^4
    let (n, x) = {
        let v: Vec<usize> = read_tokens();
        (v[0], v[1])
    };

    let mut ls: Vec<usize> = vec![];
    for _ in 0..n {
        // a, b ~ 10^2
        let v: Vec<usize> = read_tokens();
        ls.extend((0..v[1]).map(|_| v[0]));
    }

    // dp(s, k) = true \iff ...
    let m = ls.len();
    let mut dp: Vec<Vec<bool>> = vec![vec![false; m + 1]; x + 1];
    dp[0][0] = true;

    for s in 0..(x + 1) {
        for k in 0..m {
            dp[s][k + 1] = dp[s][k] || (s >= ls[k] && dp[s - ls[k]][k]);
        }
    }

    let result = dp[x][m];
    println!("{}", if result { "Yes" } else { "No" });
}

/*
python misc/run.py atcoder/abc286/d/main.rs

%%%% begin
2 19
2 3
5 6
%%%%
Yes
%%%% end

%%%% begin
2 18
2 3
5 6
%%%%
No
%%%% end

%%%% begin
3 1001
1 1
2 1
100 10
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
