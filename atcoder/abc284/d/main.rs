// AC

// https://atcoder.jp/contests/abc284/tasks/abc284_d

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // [1, 9 x 10^18]
    let n: usize = read_tokens()?[0];

    // find smallest factor f <= n^1/3
    let mut p = (2..).find(|f| n % f == 0).unwrap();

    // fix up square factor
    if n % (p * p) != 0 {
        p = isqrt(n / p);
    }

    println!("{} {}", p, n / p / p);
    Ok(())
}

fn isqrt(n: usize) -> usize {
    // ((1 << 32) - 1) ** 2 = 18446744065119617025 ~ 1.8 x 10^19
    binary_search_max(0, (1 << 32) - 1, |p| p * p <= n)
}

fn main() -> io::Result<()> {
    let t: usize = read_tokens()?[0];
    for _ in 0..t {
        main_case()?
    }
    Ok(())
}

/*
python misc/run.py atcoder/abc284/d/main.rs

%%%% begin
3
2023
63
1059872604593911
%%%%
17 7
3 7
104149 97711
%%%% end
*/

//
// utils
//

// max { x \in [x0, x1) | f(x) }
fn binary_search_max<F: Fn(usize) -> bool>(mut x0: usize, mut x1: usize, f: F) -> usize {
    assert!(f(x0));
    while x0 + 1 < x1 {
        let x = (x0 + x1) / 2;
        if f(x) {
            x0 = x;
        } else {
            x1 = x;
        }
    }
    x0
}

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
