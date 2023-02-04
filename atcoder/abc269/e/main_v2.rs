// AC

// https://atcoder.jp/contests/abc269/tasks/abc269_e

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let n: usize = read_tokens()?[0];

    //
    // split rows/columns and binary search a row/column without rook
    //

    let ask_i = |i1: usize, i2: usize| {
        println!("? {} {} {} {}", i1 + 1, i2, 1, n);
        read_tokens::<usize>().map(|v| v[0])
    };

    let ask_j = |i1: usize, i2: usize| {
        println!("? {} {} {} {}", 1, n, i1 + 1, i2);
        read_tokens::<usize>().map(|v| v[0])
    };

    let result_i: usize;
    let result_j: usize;

    //
    // solve row
    //
    {
        let mut i1 = 0;
        let mut i2 = n;
        while i1 + 1 < i2 {
            let i = (i1 + i2) / 2;
            if ask_i(i1, i)? < i - i1 {
                i2 = i;
            } else {
                i1 = i;
            }
        }
        result_i = i1;
    }

    //
    // solve column
    //
    {
        let mut i1 = 0;
        let mut i2 = n;
        while i1 + 1 < i2 {
            let i = (i1 + i2) / 2;
            if ask_j(i1, i)? < i - i1 {
                i2 = i;
            } else {
                i1 = i;
            }
        }
        result_j = i1;
    }

    println!("! {} {}", result_i + 1, result_j + 1);
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
    for token in line.trim().split(' ') {
        let value: F = token
            .parse()
            .map_err(|e| io::Error::new(io::ErrorKind::Other, format!("{:?}", e)))?;
        result.push(value);
    }
    Ok(result)
}
