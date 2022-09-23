// WA

// https://atcoder.jp/contests/abc269/tasks/abc269_e

// read the spec wrong (the last rook also has to satisfy the condition.)

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let n: usize = read_tokens()?[0];

    //
    // split rows and binary search a row without rook
    //

    let ask = |i1: usize, i2: usize| {
        println!("? {} {} {} {}", i1 + 1, i2, 1, n);
        read_tokens::<usize>().map(|v| v[0])
    };

    let answer = |i: usize| -> () {
        println!("! {} {}", i + 1, 1);
    };

    let mut i1 = 0;
    let mut i2 = n;
    while i1 + 1 < i2 {
        let i = (i1 + i2) / 2;
        if ask(i1, i)? < i - i1 {
            i2 = i;
        } else {
            i1 = i;
        }
    }

    answer(i1);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc269/e/main.rs

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
