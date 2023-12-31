// AC

// https://atcoder.jp/contests/abc317/tasks/abc317_c

fn main() {
    // n ~ 10
    let [n, m]: [usize; 2] = read_array();
    let mut adj: Vec<Vec<Option<usize>>> = vec![vec![None; n]; n];
    for _ in 0..m {
        let [a, b, c]: [usize; 3] = read_array();
        adj[a - 1][b - 1] = Some(c);
        adj[b - 1][a - 1] = Some(c);
    }

    // dp(s, i) = maximum travel length to visit subset "s" and reach "i"
    let mut dp: Vec<Vec<Option<usize>>> = vec![vec![None; n]; 1 << n];

    for i in 0..n {
        dp[1 << i][i] = Some(0);
    }

    for s in 0..(1 << n) {
        for i in 0..n {
            if s & (1 << i) == 0 {
                continue;
            }
            for j in 0..n {
                if s & (1 << j) != 0 {
                    continue;
                }
                let s2 = s | (1 << j);
                dp[s2][j] = dp[s2][j].max(add_opion(dp[s][i], adj[i][j]));
            }
        }
    }

    let result = dp
        .iter()
        .flat_map(|v| v.iter().max())
        .flatten()
        .max()
        .unwrap();
    println!("{}", result);
}

fn add_opion(x: Option<usize>, y: Option<usize>) -> Option<usize> {
    x.and_then(|x| y.map(|y| x + y))
}

/*
python misc/run.py atcoder/abc317/c/main.rs

%%%% begin
4 4
1 2 1
2 3 10
1 3 100
1 4 1000
%%%%
1110
%%%% end

%%%% begin
10 1
5 9 1
%%%%
1
%%%% end

%%%% begin
10 13
1 2 1
1 10 1
2 3 1
3 4 4
4 7 2
4 8 1
5 8 1
5 9 3
6 8 1
6 9 5
7 8 1
7 9 4
9 10 3
%%%%
20
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
