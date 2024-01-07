// AC

// https://atcoder.jp/contests/abc321/tasks/abc321_d

fn main() {
    // n, m ~ 10^5
    // p ~ 10^8
    let [n, m, p]: [usize; 3] = read_array();
    let mut ls1: Vec<usize> = read_vec();
    let mut ls2: Vec<usize> = read_vec();

    // WLOG
    ls1.sort();
    ls2.sort();

    // cumsum
    let mut sum2: Vec<usize> = vec![0; m + 1];
    for j in 0..m {
        sum2[j + 1] = sum2[j] + ls2[j];
    }

    let mut result: usize = 0;
    for i in 0..n {
        // (Ai + B0) + ... + (Ai + Bk-1) + P + ... + P
        let a = ls1[i];
        let k = ls2.partition_point(|&b| a + b < p);
        result += a * k + sum2[k] + p * (m - k);
    }
    println!("{}", result);
}

/*
python misc/run.py atcoder/abc321/d/main.rs

%%%% begin
2 2 7
3 5
6 1
%%%%
24
%%%% end

%%%% begin
1 3 2
1
1 1 1
%%%%
6
%%%% end

%%%% begin
7 12 25514963
2436426 24979445 61648772 23690081 33933447 76190629 62703497
11047202 71407775 28894325 31963982 22804784 50968417 30302156 82631932 61735902 80895728 23078537 7723857
%%%%
2115597124
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
