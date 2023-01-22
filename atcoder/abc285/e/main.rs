// WIP

// https://atcoder.jp/contests/abc285/tasks/abc285_e

fn main() {
    // ~ 10^4
    let n: usize = read_tokens()[0];
    let ls: Vec<usize> = read_tokens();

    // dp(k) = ...
    let mut dp: Vec<usize> = vec![0; n + 1];
    for k in 2..=n {
        // holiday only at 0
        for i in 1..k {
            dp[k] += ls[i.min(k - i) - 1];
        }

        // holiday at l
        for l in 1..k {
            dp[k] = dp[k].max(dp[l] + dp[k - l]);
        }
    }

    let result = dp[n];
    println!("{}", result);
}

/*
python misc/run.py atcoder/abc285/e/main.rs

%%%% begin
7
10 10 1 1 1 1 1
%%%%
50
%%%% end

%%%% begin
10
200000000 500000000 1000000000 800000000 100000000 80000000 600000 900000000 1 20
%%%%
5100000000
%%%% end

%%%% begin
20
38 7719 21238 2437 8855 11797 8365 32285 10450 30612 5853 28100 1142 281 20537 15921 8945 26285 2997 14680
%%%%
236980
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
