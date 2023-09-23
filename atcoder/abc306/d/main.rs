// AC

// https://atcoder.jp/contests/abc306/tasks/abc306_d

fn main() {
    // ~ 10^5
    let n: usize = read_tokens()[0];

    // y ~ [-10^9, 10^9]
    let ls: Vec<Vec<isize>> = (0..n).map(|_| read_tokens()).collect();

    // dp[k][0] = max score at k-th step being healthy
    // dp[k][1] = max score at k-th step being upset
    let mut dp: Vec<Vec<isize>> = vec![vec![0; 2]; n + 1];

    for i in 0..n {
        match ls[i][0] {
            0 => {
                dp[i + 1][0] = dp[i][0].max(dp[i][0].max(dp[i][1]) + ls[i][1]);
                dp[i + 1][1] = dp[i][1].max(dp[i][1] + ls[i][1]);
            }
            1 => {
                dp[i + 1][0] = dp[i][0];
                dp[i + 1][1] = dp[i][1].max(dp[i][0] + ls[i][1]);
            }
            _ => unreachable!(),
        }
    }

    let result = dp[n][0].max(dp[n][1]);
    println!("{}", result);
}

/*
python misc/run.py atcoder/abc306/d/main.rs

%%%% begin
5
1 100
1 300
0 -200
1 500
1 300
%%%%
600
%%%% end

%%%% begin
4
0 -1
1 -2
0 -3
1 -4
%%%%
0
%%%% end

%%%% begin
15
1 900000000
0 600000000
1 -300000000
0 -700000000
1 200000000
1 300000000
0 -600000000
1 -900000000
1 600000000
1 -100000000
1 -400000000
0 900000000
0 200000000
1 -500000000
1 900000000
%%%%
4100000000
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
