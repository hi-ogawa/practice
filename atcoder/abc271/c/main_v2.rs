// WAs

// https://atcoder.jp/contests/abc271/tasks/abc271_c

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let n: usize = read_tokens()?[0]; // 3 x 10^5

    let mut ls: Vec<usize> = read_tokens()?; // [1, 10^9]
    ls.dedup();

    //
    // binary search
    //

    let evaluate = |k: usize| -> bool {
        let used = ls.iter().filter(|&&x| x <= k).count();
        k <= used + (n - used) / 2
    };

    let result = binary_search(0, n + 1, evaluate);
    println!("{}", result);

    Ok(())
}

fn binary_search<F: Fn(usize) -> bool>(mut x0: usize, mut x1: usize, f: F) -> usize {
    assert!(f(x0));
    assert!(!f(x1));
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

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc271/c/main_v2.rs

%%%% begin
6
1 2 4 6 7 271
%%%%
4
%%%% end

%%%% begin
10
1 1 1 1 1 1 1 1 1 1
%%%%
5
%%%% end

%%%% begin
1
5
%%%%
0
%%%% end

// custom
%%%% begin
4
1 1 1 3
%%%%
3
%%%% end

// custom
%%%% begin
4
1 2 3 4
%%%%
4
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
