// AC

// https://atcoder.jp/contests/abc311/tasks/abc311_c

fn main() {
    // 10^5
    let n: usize = read_vec()[0];
    let ls: Vec<usize> = read_vec::<usize>().iter().map(|i| i - 1).collect();

    let mut visited: Vec<bool> = vec![false; n];
    let mut v = 0;
    loop {
        visited[v] = true;
        let u = ls[v];
        if visited[u] {
            break;
        }
        v = u;
    }

    let last = v;
    let mut next = ls[v];
    let mut result: Vec<usize> = vec![next];
    while next != last {
        next = ls[next];
        result.push(next);
    }

    println!(
        "{}\n{}",
        result.len(),
        result
            .iter()
            .map(|i| (i + 1).to_string())
            .collect::<Vec<_>>()
            .join(" ")
    );
}

/*
python misc/run.py atcoder/abc311/c/main.rs

%%%% begin
7
6 7 2 1 3 4 5
%%%%
4
7 5 3 2
%%%% end

%%%% begin
2
2 1
%%%%
2
1 2
%%%% end

%%%% begin
8
3 7 4 7 3 3 8 2
%%%%
3
2 7 8
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
