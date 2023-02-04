// AC

// https://atcoder.jp/contests/abc267/tasks/abc267_d

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // n, m \in [1, 2000]
    let (n, m): (usize, _) = read_tokens().map(|v| (v[0], v[1]))?;

    // a \in [-2 x 10^5, 2 x 10^5]
    let ls: Vec<isize> = read_tokens()?;

    //
    // dp(i, k) = optimal solution for the sub problem (B1, .., Bi) picked from (A1, ..., Ak)
    //
    // then
    //  dp(0, 0) = 0
    //  dp(i, 0) = -inf (i > 0)
    //  dp(i, k) = max( dp(i-1, k-1) + k x ls[k-1], max{ dp(i, l) | l < k } )
    let mut dp: Vec<Vec<isize>> = vec![vec![0; n + 1]; m + 1];
    for i in 1..=m {
        dp[i][0] = -1e12 as isize;
    }
    for i in 1..=m {
        let mut acc = dp[i][0];
        for k in 1..=n {
            acc = acc.max(dp[i - 1][k - 1] + (i as isize) * ls[k - 1]);
            dp[i][k] = acc;
            // dbg!((i, k, acc));
        }
    }

    let result = dp[m][n];
    println!("{}", result);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc267/d/main.rs

%%%% begin
4 2
5 4 -1 8
%%%%
21
%%%% end

%%%% begin
10 4
-3 1 -4 1 -5 9 -2 6 -5 3
%%%%
54
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
