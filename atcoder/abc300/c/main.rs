// WIP

// https://atcoder.jp/contests/abc300/tasks/abc300_c

fn main() {
}

/*
python misc/run.py atcoder/abc300/c/main.rs

*/

//
// utils
//

#[allow(dead_code)]
fn read_tokens<T: std::str::FromStr>() -> Vec<T>
where
    <T as std::str::FromStr>::Err: std::fmt::Debug,
{
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).unwrap();
    line.split_whitespace()
        .map(|s| s.parse().unwrap())
        .collect()
}
