// AC

// https://atcoder.jp/contests/abc270/tasks/abc270_e

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // n <= 10^5
    // k <= 10^12
    let (n, k) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;
    let ls: Vec<usize> = read_tokens()?;

    // sort indices
    let mut order: Vec<usize> = (0..n).collect();
    order.sort_by_key(|&i| ls[i]);

    // find which baskets will be completely eaten
    let mut k = k;
    let mut eaten: Vec<bool> = vec![false; n];
    let mut last: usize = 0;
    for (t, &i) in order.iter().enumerate() {
        let m = (ls[i] - last) * (n - t);
        if m > k {
            break;
        }
        k -= m;
        eaten[i] = true;
        last = ls[i];
    }

    // take care the remainder
    let mut result: Vec<usize> = (0..n)
        .map(|i| if eaten[i] { 0 } else { ls[i] - last })
        .collect();
    let left: Vec<usize> = (0..n).filter(|&i| !eaten[i]).collect();
    if left.len() > 0 {
        let q = k / left.len();
        let m = k % left.len();
        for (s, &i) in left.iter().enumerate() {
            result[i] -= if s < m { q + 1 } else { q };
        }
    }

    println!(
        "{}",
        result
            .iter()
            .map(|v| v.to_string())
            .collect::<Vec<_>>()
            .join(" ")
    );
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc270/e/main.rs

%%%% begin
3 3
1 3 0
%%%%
0 1 0
%%%% end

%%%% begin
2 1000000000000
1000000000000 1000000000000
%%%%
500000000000 500000000000
%%%% end

%%%% begin
4 10
1 2 3 4
%%%%
0 0 0 0
%%%% end
*/

//
// utils
//

#[allow(dead_code)]
fn read_tokens<F: FromStr>() -> io::Result<Vec<F>>
where
    <F as FromStr>::Err: Debug,
{
    let mut line = String::new();
    io::stdin().read_line(&mut line)?;
    let mut result: Vec<F> = Vec::new();
    for token in line.trim().split(' ') {
        let value: F = token
            .parse()
            .map_err(|e| io::Error::new(io::ErrorKind::Other, format!("{:?}", e)))?;
        result.push(value);
    }
    Ok(result)
}
