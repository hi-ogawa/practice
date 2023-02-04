// AC

// https://atcoder.jp/contests/abc266/tasks/abc266_e

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let n = read_tokens::<usize>()?[0]; // [1, 100]
    let mut ls: Vec<f64> = vec![0.0; n + 1];

    for i in 1..=n {
        for j in 1..=6 {
            let j = f64::from(j);
            ls[i] += ls[i - 1].max(j);
        }
        ls[i] /= 6.0;
    }

    let result = ls[n];
    println!("{}", result);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc266/e/main.rs

%%%% begin
1
%%%%
3.5000000000
%%%% end

%%%% begin
2
%%%%
4.2500000000
%%%% end

%%%% begin
10
%%%%
5.6502176688
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
