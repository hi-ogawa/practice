// WIP

// {{PROBLEM_URL}}

fn main() {
    let [t] = read_array();
    for _ in 0..t {}
}

/*
python misc/run.py {{FILE}}

{{TESTS}}
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
    use std::convert::TryInto;
    read_vec::<T>().try_into().ok().unwrap()
}
