// AFTER EDITORIAL, AC

// https://atcoder.jp/contests/abc275/tasks/abc275_d

use std::collections::HashMap;

fn main_case() {
    // n \in [0, 10^18]
    let n: usize = read_tokens()[0];

    //
    // Prop.
    //   floor(floor(n / p) / q) = floor(n / p q)
    //

    //
    // Prop.
    //   define S = { f(floor(n / 2^i 3^j)) | i <= k, j <= l }, then
    //     1. f is "closed" under S
    //     2. |S| <= log2(n) log3(n)
    //

    let k = ceil_log(2, n);
    let l = ceil_log(3, n);
    let mut dp: Vec<Vec<usize>> = vec![vec![0; l + 1]; k + 1];
    dp[0][0] = n;
    for j in 0..l {
        dp[0][j + 1] = dp[0][j] / 3;
    }
    for i in 0..k {
        for j in 0..=l {
            dp[i + 1][j] = dp[i][j] / 2;
        }
    }

    let mut f: HashMap<usize, usize> = HashMap::new();
    f.insert(0, 1);
    for i in (0..=k).rev() {
        for j in (0..=l).rev() {
            let x = dp[i][j];
            if x > 0 {
                f.insert(x, f[&(x / 2)] + f[&(x / 3)]);
            }
        }
    }

    let result = f[&n];
    println!("{}", result);
}

fn ceil_log(b: usize, mut x: usize) -> usize {
    assert!(b > 0);
    let mut result = 0;
    while x > 0 {
        x /= b;
        result += 1;
    }
    result
}

fn main() {
    main_case();
}

/*
python misc/run.py atcoder/abc275/d/main_v2.rs

%%%% begin
2
%%%%
3
%%%% end

%%%% begin
0
%%%%
1
%%%% end

%%%% begin
100
%%%%
55
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
