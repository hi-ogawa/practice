// AC

// https://atcoder.jp/contests/abc318/tasks/abc318_e

fn main() {
    // n ~ 10^5
    let n: usize = read_vec()[0];
    // x \in [1, n]
    let ls: Vec<usize> = read_vec();

    let mut value_to_indices: Vec<Vec<usize>> = vec![vec![]; n + 1];
    for (i, &x) in ls.iter().enumerate() {
        value_to_indices[x].push(i);
    }

    let mut result = 0;
    for indices in &value_to_indices {
        let k = indices.len();
        if k == 0 {
            continue;
        }
        for i in 0..(k - 1) {
            result += (i + 1) * (k - 1 - i) * (indices[i + 1] - indices[i] - 1)
        }
    }
    println!("{}", result);
}

/*
python misc/run.py atcoder/abc318/e/main.rs

%%%% begin
5
1 2 1 3 2
%%%%
3
%%%% end

%%%% begin
7
1 2 3 4 5 6 7
%%%%
0
%%%% end

%%%% begin
13
9 7 11 7 3 8 1 13 11 11 11 6 13
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
