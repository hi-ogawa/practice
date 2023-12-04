// AC

// https://atcoder.jp/contests/abc313/tasks/abc313_c

fn main() {
    // n ~ 10^5
    let n: usize = read_vec()[0];
    let mut ls: Vec<usize> = read_vec();
    ls.sort();

    // solve x, k where
    //   x = floor(s / n)
    //   s = x (n - k) + (x + 1) k = x n + k
    let s: usize = ls.iter().sum();
    let x = s / n;
    let k = s - x * n;

    let mut result: usize = 0;
    for &y in &ls[0..(n - k)] {
        result += y.abs_diff(x);
    }
    for &y in &ls[(n - k)..] {
        result += y.abs_diff(x + 1);
    }
    assert!(result % 2 == 0);
    println!("{}", result / 2);
}

/*
python misc/run.py atcoder/abc313/c/main.rs

%%%% begin
4
4 7 3 7
%%%%
3
%%%% end

%%%% begin
1
313
%%%%
0
%%%% end

%%%% begin
10
999999997 999999999 4 3 2 4 999999990 8 999999991 999999993
%%%%
2499999974
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
