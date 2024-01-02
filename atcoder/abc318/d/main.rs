// AC

// https://atcoder.jp/contests/abc318/tasks/abc318_d

fn main() {
    // n ~ 16
    let n: usize = read_vec()[0];
    let mut adj: Vec<Vec<usize>> = vec![vec![0; n]; n];
    for i in 0..n {
        let ws: Vec<usize> = read_vec();
        for (j, w) in ((i + 1)..n).zip(ws) {
            adj[i][j] = w;
            adj[j][i] = w;
        }
    }

    // dp(S, i) = (maximum weights using subset "S" and ending with "i" where edges are taken for 0th-1th, 2th-3rd, ...)
    let mut dp: Vec<Vec<usize>> = vec![vec![0; n]; 1 << n];

    for s in 0..(1 << n) {
        for i in 0..n {
            if s & (1 << i) == 0 {
                continue;
            }
            for j in 0..n {
                if s & (1 << j) != 0 {
                    continue;
                }
                let mut next = dp[s][i];
                if s.count_ones() % 2 == 1 {
                    next += adj[i][j];
                }
                let s2 = s | (1 << j);
                dp[s2][j] = dp[s2][j].max(next)
            }
        }
    }

    let result = dp[(1 << n) - 1].iter().max().unwrap();
    println!("{}", result);
}

/*
python misc/run.py atcoder/abc318/d/main.rs

%%%% begin
4
1 5 4
7 8
6
%%%%
13
%%%% end

%%%% begin
3
1 2
3
%%%%
3
%%%% end

%%%% begin
16
5 6 5 2 1 7 9 7 2 5 5 2 4 7 6
8 7 7 9 8 1 9 6 10 8 8 6 10 3
10 5 8 1 10 7 8 4 8 6 5 1 10
7 4 1 4 5 4 5 10 1 5 1 2
2 9 9 7 6 2 2 8 3 5 2
9 10 3 1 1 2 10 7 7 5
10 6 1 8 9 3 2 4 2
10 10 8 9 2 10 7 9
5 8 8 7 5 8 2
4 2 2 6 8 3
2 7 3 10 3
5 7 10 3
8 5 7
9 1
4
%%%%
75
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
