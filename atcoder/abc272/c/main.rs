// AC

// https://atcoder.jp/contests/abc272/tasks/abc272_c

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let _n: usize = read_tokens()?[0];
    let mut ls: Vec<isize> = read_tokens()?;
    ls.sort();
    ls.reverse();

    let evens: Vec<_> = ls.iter().filter(|&x| x % 2 == 0).collect();
    let odds: Vec<_> = ls.iter().filter(|&x| x % 2 == 1).collect();

    let mut result = -1;
    if evens.len() >= 2 {
        result = result.max(evens[0] + evens[1]);
    }
    if odds.len() >= 2 {
        result = result.max(odds[0] + odds[1]);
    }
    println!("{}", result);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc272/c/main.rs

%%%% begin
3
2 3 4
%%%%
6
%%%% end

%%%% begin
2
1 0
%%%%
-1
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
