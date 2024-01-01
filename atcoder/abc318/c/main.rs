// AC

// https://atcoder.jp/contests/abc318/tasks/abc318_c

fn main() {
    // n, d ~ 10^5
    let [_n, d, f]: [usize; 3] = read_array();
    let mut ls: Vec<usize> = read_vec();

    // sort descending
    ls.sort();
    ls.reverse();

    // chunk by "d" and use batch ticket if cheaper
    let result: usize = ls.chunks(d).map(|chunk| f.min(chunk.iter().sum())).sum();
    println!("{}", result);
}

/*
python misc/run.py atcoder/abc318/c/main.rs

%%%% begin
5 2 10
7 1 6 3 6
%%%%
20
%%%% end

%%%% begin
3 1 10
1 2 3
%%%%
6
%%%% end

%%%% begin
8 3 1000000000
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000
%%%%
3000000000
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
