// WA

// https://atcoder.jp/contests/abc376/tasks/abc376_e

fn main() {
    let t: usize = read_vec()[0];
    for _ in 0..t {
        solve()
    }
}

fn solve() {
    // PROP.
    //   1. sort by b
    //   2. then, optimal is a one of
    //        1, 2, .., k-1, k
    //        1, 2, .., k-1,   k+1
    //        1, 2, .., k-1,       k+2
    //        ...
    //        1, 2, .., k-1,            n

    // n, k ~ 10^5
    // a, b ~ 10^6
    let [n, k]: [usize; 2] = read_array();
    let ls1: Vec<usize> = read_vec();
    let ls2: Vec<usize> = read_vec();
    let mut ls: Vec<(usize, usize)> = ls1.into_iter().zip(ls2.into_iter()).collect();
    ls.sort_by_key(|&(_a, b)| b);

    let a_base = ls[0..k - 1].iter().map(|x| x.0).max().unwrap_or(0);
    let b_base = ls[0..k - 1].iter().map(|x| x.1).sum::<usize>();
    let result = ls[k - 1..n]
        .iter()
        .map(|&(a, b)| a_base.max(a) * (b_base + b))
        .min()
        .unwrap();
    println!("{}", result);
}

/*
python misc/run.py atcoder/abc376/e/main.rs

%%%% begin
3
3 2
3 7 6
9 2 4
5 3
6 4 1 5 9
8 6 5 1 7
10 6
61 95 61 57 69 49 46 47 14 43
39 79 48 92 90 76 30 16 30 94
%%%%
42
60
14579
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
