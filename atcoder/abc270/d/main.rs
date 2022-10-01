// WA

// https://atcoder.jp/contests/abc270/tasks/abc270_d

// TODO: prove

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let (n, _) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;
    let ls: Vec<usize> = read_tokens()?;

    let mut n = n;
    let mut turn = 0;
    let mut result: [usize; 2] = [0, 0];
    while n > 0 {
        let x = ls.iter().filter(|&&x| x <= n).last().unwrap();
        n -= x;
        result[turn] += x;
        turn ^= 1;
    }

    println!("{}", result[0]);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc270/d/main.rs

%%%% begin
10 2
1 4
%%%%
5
%%%% end

%%%% begin
11 4
1 2 3 6
%%%%
8
%%%% end

%%%% begin
10000 10
1 2 4 8 16 32 64 128 256 512
%%%%
5136
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
    for token in line.trim().split(" ") {
        let value: F = token
            .parse()
            .map_err(|e| io::Error::new(io::ErrorKind::Other, format!("{:?}", e)))?;
        result.push(value);
    }
    Ok(result)
}
