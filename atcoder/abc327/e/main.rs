// WA

// https://atcoder.jp/contests/abc327/tasks/abc327_e

fn main() {
    // n ~ 5000
    let n: usize = read_vec()[0];
    let ls: Vec<f64> = read_vec();

    const C1: f64 = 0.9;
    const C2: f64 = 1200.0;

    // dp(n, k) = (optimal of "∑ (0.9)^(k - i) Qi" when picking "k" out of "P1" .. "Pn")
    let mut dp: Vec<Vec<f64>> = vec![vec![f64::MIN; n + 1]; n + 1];
    dp[0][0] = 0.0;
    for i in 0..n {
        for k in 0..=i {
            let next = C1 * dp[i][k] + ls[i];
            dp[i + 1][k + 1] = next.max(dp[i][k + 1]);
        }
    }

    let mut result = f64::MIN;
    for k in 1..=n {
        let denom = (1.0 - C1.powf(k as f64)) / (1.0 - C1);
        let next = dp[n][k] / denom - C2 / (k as f64).sqrt();
        result = result.max(next);
    }
    println!("{}", result);
}

/*
python misc/run.py atcoder/abc327/e/main.rs

%%%% begin
3
1000 600 1200
%%%%
256.735020470879931
%%%% end

%%%% begin
3
600 1000 1200
%%%%
261.423219407873489
%%%% end

%%%% begin
1
100
%%%%
-1100.000000000000000
%%%% end
*/

//
// utils
//

#[allow(dead_code)]
fn read_vec<T: std::str::FromStr>() -> Vec<T> {
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).unwrap();
    line.split_whitespace()
        .map(|s| s.parse().ok().unwrap())
        .collect()
}

#[allow(dead_code)]
fn read_array<T: std::str::FromStr, const LEN: usize>() -> [T; LEN] {
    #[allow(unused_imports)]
    use std::convert::TryInto;
    read_vec::<T>().try_into().ok().unwrap()
}
