// WA

// https://atcoder.jp/contests/abc310/tasks/abc310_e

// NAND doesn't distribute like this...

fn main() {
    let n: usize = read_vec()[0];
    let ls: Vec<usize> = read_vec::<String>()[0]
        .chars()
        .map(|c| if c == '1' { 1 } else { 0 })
        .collect();

    // find first 0 on the right for each i
    let mut first_zero: Vec<Option<usize>> = vec![None; n + 1];
    for i in (0..n).rev() {
        first_zero[i] = if ls[i] == 0 {
            Some(i)
        } else {
            first_zero[i + 1]
        };
    }
    dbg!(&first_zero);

    let mut result = 0;
    for i in 0..n {
        result += ls[i];
        if let Some(j) = first_zero[i] {
            result += n - j;
            // correct edge case
            if j == i {
                result -= 1;
            }
        }
    }

    println!("{}", result);
}

/*
python misc/run.py atcoder/abc310/e/main.rs

%%%% begin
5
00110
%%%%
9
%%%% end

%%%% begin
30
101010000100101011010011000010
%%%%
326
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
