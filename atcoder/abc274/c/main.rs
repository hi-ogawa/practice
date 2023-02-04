// AC

// https://atcoder.jp/contests/abc274/tasks/abc274_c

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let n: usize = read_tokens()?[0];
    let ls: Vec<usize> = read_tokens()?;

    let mut result: Vec<usize> = vec![0; 2 * n + 2];

    for (i, &a) in ls.iter().enumerate() {
        result[2 * (i + 1)] = result[a] + 1;
        result[2 * (i + 1) + 1] = result[a] + 1;
    }

    for r in &result[1..] {
        println!("{}", r);
    }
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc274/c/main.rs

%%%% begin
2
1 2
%%%%
0
1
1
2
2
%%%% end

%%%% begin
4
1 3 5 2
%%%%
0
1
1
2
2
3
3
2
2
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
