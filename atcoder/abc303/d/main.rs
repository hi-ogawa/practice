// AC

// https://atcoder.jp/contests/abc303/tasks/abc303_d

fn main() {
    let v: Vec<usize> = read_tokens();
    let (x, y, z) = (v[0], v[1], v[2]);
    let s: Vec<char> = read_tokens::<String>()[0].clone().chars().collect();
    let n = s.len();

    // dp[i][on/off] = { min cost to complete i-th prefix with CapsLock on/off }
    let mut dp: Vec<[usize; 2]> = vec![[0; 2]; n + 1];
    dp[0][1] = z;

    for i in 0..n {
        match s[i] {
            'a' => {
                dp[i + 1][0] = (dp[i][0] + x).min(dp[i][1] + z + x).min(dp[i][1] + y + z);
                dp[i + 1][1] = (dp[i][1] + y).min(dp[i][0] + z + y).min(dp[i][0] + x + z);
            }
            'A' => {
                dp[i + 1][0] = (dp[i][0] + y).min(dp[i][1] + z + y).min(dp[i][1] + x + z);
                dp[i + 1][1] = (dp[i][1] + x).min(dp[i][0] + z + x).min(dp[i][0] + y + z);
            }
            _ => unreachable!(),
        }
    }

    let result = dp[n][0].min(dp[n][1]);
    println!("{}", result);
}

/*
python misc/run.py atcoder/abc303/d/main.rs

%%%% begin
1 3 3
AAaA
%%%%
9
%%%% end

%%%% begin
1 1 100
aAaAaA
%%%%
6
%%%% end

%%%% begin
1 2 4
aaAaAaaAAAAaAaaAaAAaaaAAAAA
%%%%
40
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
