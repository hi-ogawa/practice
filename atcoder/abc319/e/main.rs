// AC

// https://atcoder.jp/contests/abc319/tasks/abc319_e

fn main() {
    // n ~ 10^5
    let [n, x, y]: [usize; 3] = read_array();
    // p ~ 8
    let ls: Vec<[usize; 2]> = (0..(n - 1)).map(|_| read_array()).collect();
    // nq ~ 10^5
    let nq: usize = read_vec()[0];
    let qs: Vec<usize> = (0..nq).map(|_| read_vec()[0]).collect();

    // PROP. period is at most LMS(p1, p2, ...) (TODO: prove)
    let k = (1..=8).fold(1, |x, y| lms(x, y)); // 840

    // dp(s) = time to reach last stop when starting at time "s" at 1st step
    let mut dp: Vec<usize> = (0..k).collect();
    for &[p, t] in &ls {
        for s in 0..k {
            dp[s] = dp[s] + (p - dp[s] % p) % p + t;
        }
    }

    for q in qs {
        let t1 = q + x;
        let t2 = t1 + dp[t1 % k] - t1 % k;
        let t3 = t2 + y;
        println!("{}", t3);
    }
}

fn lms(x: usize, y: usize) -> usize {
    (x * y) / gcd(x, y)
}

fn gcd(mut x: usize, mut y: usize) -> usize {
    if x < y {
        [x, y] = [y, x];
    }
    while y > 0 {
        [x, y] = [y, x % y];
    }
    x
}

/*
python misc/run.py atcoder/abc319/e/main.rs

%%%% begin
4 2 3
5 4
6 6
3 1
7
13
0
710511029
136397527
763027379
644706927
447672230
%%%%
34
22
710511052
136397548
763027402
644706946
447672250
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
