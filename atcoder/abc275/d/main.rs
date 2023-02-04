// RE

// https://atcoder.jp/contests/abc275/tasks/abc275_d

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // ~ 10^18
    let n: usize = read_tokens()?[0];

    let mut dp: Vec<usize> = vec![0; n + 1];
    dp[0] = 1;

    let mut update = |dst: usize, src: usize| {
        if src != dst && dst <= n {
            dp[dst] += dp[src];
        }
    };

    for x in 0..n {
        update(2 * x, x);
        update(2 * x + 1, x);
        update(3 * x, x);
        update(3 * x + 1, x);
        update(3 * x + 2, x);
    }
    dbg!(&dp);

    let result = dp[n];
    println!("{}", result);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc275/d/main.rs

%%%% begin
2
%%%%
3
%%%% end

%%%% begin
0
%%%%
1
%%%% end

%%%% begin
100
%%%%
55
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
