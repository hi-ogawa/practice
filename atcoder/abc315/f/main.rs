// AC

// https://atcoder.jp/contests/abc315/tasks/abc315_f

fn main() {
    // n ~ 10^4
    let n: usize = read_vec()[0];
    // x, y ~ 10^4
    let ls: Vec<[f64; 2]> = (0..n).map(|_| read_array()).collect();

    // sum of maximum distance is at most n x d ~ 10^8 ~ 2^27
    // thus we don't need to consider when skip count exceeds 30 or so

    // dp(n, k) = (min distance sum to reach "n" with "k" checkpoints skpped)
    let k = 30;
    let mut dp: Vec<Vec<f64>> = vec![vec![1e10; k]; n + 1];
    dp[1][0] = 0.0;

    // O(n k^2)
    for i in 1..n {
        for l in 0..k {
            for s in 0..=(l.min(i - 1)) {
                let j = i - s - 1;
                dp[i + 1][l] = dp[i + 1][l].min(dp[j + 1][l - s] + get_distance(ls[i], ls[j]));
            }
        }
    }

    let result = (0..k)
        .map(|l| dp[n][l] + if l > 0 { (1 << (l - 1)) as f64 } else { 0.0 })
        .reduce(f64::min)
        .unwrap();
    println!("{}", result);
}

fn get_distance([x1, y1]: [f64; 2], [x2, y2]: [f64; 2]) -> f64 {
    let x = x1 - x2;
    let y = y1 - y2;
    (x * x + y * y).sqrt()
}

/*
python misc/run.py atcoder/abc315/f/main.rs

%%%% begin
6
0 0
1 1
2 0
0 1
1 0
2 1
%%%%
5.82842712474619009753
%%%% end

%%%% begin
10
1 8
3 7
9 4
4 9
6 1
7 5
0 0
1 3
6 8
6 4
%%%%
24.63441361516795872523
%%%% end

%%%% begin
10
34 24
47 60
30 31
12 97
87 93
64 46
82 50
14 7
17 24
3 78
%%%%
110.61238353245736230207
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
