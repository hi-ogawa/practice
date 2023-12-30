// AC

// https://atcoder.jp/contests/abc317/tasks/abc317_d

fn main() {
    // n ~ 100
    // x, y ~ 10^9
    // sum(z) ~ 10^5
    let n: usize = read_vec()[0];

    // cost: necessary move to win
    let mut rewards: Vec<usize> = vec![];
    let mut costs: Vec<usize> = vec![];
    for _ in 0..n {
        let [x, y, z]: [usize; 3] = read_array();
        rewards.push(z);
        costs.push(if x > y { 0 } else { (y - x) / 2 + 1 });
    }

    // target sum of rewards
    let m = rewards.iter().sum::<usize>();
    let z_goal = m / 2 + 1;

    // dp(n, z) = (minimum cost to obtain "z" seats using only first "n" items)
    let mut dp: Vec<Vec<Option<usize>>> = vec![vec![None; m + 1]; n + 1];
    dp[0][0] = Some(0);

    for i in 0..n {
        for z in 0..=m {
            let next = if z >= rewards[i] {
                if let Some(c) = dp[i][z - rewards[i]] {
                    Some(costs[i] + c)
                } else {
                    None
                }
            } else {
                None
            };
            dp[i + 1][z] = [dp[i][z], next].iter().flatten().min().copied();
        }
    }

    let result = dp[n][z_goal..].iter().flatten().min();
    println!("{}", result.unwrap());
}

/*
python misc/run.py atcoder/abc317/d/main.rs

%%%% begin
1
3 8 1
%%%%
3
%%%% end

%%%% begin
2
3 6 2
1 8 5
%%%%
4
%%%% end

%%%% begin
3
3 4 2
1 2 3
7 2 6
%%%%
0
%%%% end

%%%% begin
10
1878 2089 16
1982 1769 13
2148 1601 14
2189 2362 15
2268 2279 16
2394 2841 18
2926 2971 20
3091 2146 20
3878 4685 38
4504 4617 29
%%%%
86
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
