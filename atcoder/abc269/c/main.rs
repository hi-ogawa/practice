// AC

// https://atcoder.jp/contests/abc269/tasks/abc269_c

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let n: u64 = read_tokens()?[0]; // popcount(n) <= 15

    let mut x = n;
    let mut results = vec![x];
    while x > 0 {
        x = (x - 1) & n;
        results.push(x);
    }

    for x in results.iter().rev() {
        println!("{}", x);
    }
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc269/c/main.rs

%%%% begin
11
%%%%
0
1
2
3
8
9
10
11
%%%% end

%%%% begin
0
%%%%
0
%%%% end

%%%% begin
576461302059761664
%%%%
0
524288
549755813888
549756338176
576460752303423488
576460752303947776
576461302059237376
576461302059761664
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
