// WIP

// https://atcoder.jp/contests/abc313/tasks/abc313_e

fn main() {
    // n ~ 10^6
    let n: usize = read_vec()[0];
    // 1..9
    let s: Vec<char> = read_vec::<String>()[0].chars().collect();

    // sufficient/necessary condition
    //   no consecutive pair "ab" where a, b >= 2
    if (0..(n - 1)).any(|i| s[i] != '1' && s[i + 1] != '1') {
        println!("{}", -1);
        return;
    }

    todo!();
}

/*
python misc/run.py atcoder/abc313/e/main.rs

%%%% begin
3
313
%%%%
4
%%%% end

%%%% begin
9
123456789
%%%%
-1
%%%% end

%%%% begin
2
11
%%%%
1
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
