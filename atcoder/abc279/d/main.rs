// AC

// https://atcoder.jp/contests/abc279/tasks/abc279_d

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // ~ 10^18
    let (a, b) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;

    // f(x) = a (x + 1)^(-1/2) + b x
    let f = |x: usize| -> f64 {
        let x = x as f64;
        let a = a as f64;
        let b = b as f64;
        a / (x + 1.0).sqrt() + b * x
    };

    let find_convex_arg_min = || -> usize {
        let mut x0 = 0;
        let mut x1 = 1e15 as usize;
        while x0 + 2 < x1 {
            let p0 = x0 + (x1 - x0) / 3;
            let p1 = p0 + (x1 - x0) / 3;
            if f(p0) < f(p1) {
                x1 = p1;
            } else {
                x0 = p0;
            }
        }
        if f(x0) < f(x0 + 1) {
            x0
        } else {
            x0 + 1
        }
    };

    let x = find_convex_arg_min();
    // dbg!(x, f(x));

    let result = f(x);
    println!("{}", result);

    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc279/d/main.rs

%%%% begin
10 1
%%%%
7.7735026919
%%%% end

%%%% begin
5 10
%%%%
5.0000000000
%%%% end

%%%% begin
1000000000000000000 100
%%%%
8772053214538.5976562500
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
