// AC

// https://atcoder.jp/contests/abc281/tasks/abc281_d

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // ~ 100
    let (n, k, d) = read_tokens::<usize>().map(|v| (v[0], v[1], v[2]))?;
    let ls: Vec<usize> = read_tokens()?;

    // dp(i, l, c) = max { sum(A') | A' ⊆ {a1, ..., ai} and |A'| = l and sum(A') % d = c }
    let mut dp: Vec<Vec<Vec<Option<usize>>>> = vec![vec![vec![None; d]; n + 1]; n + 1];
    dp[0][0][0] = Some(0);

    for i in 1..=n {
        dp[i][0][0] = Some(0);
        let a = ls[i - 1];
        for l in 1..=i {
            for c in 0..d {
                dp[i][l][c] = [
                    dp[i - 1][l][c],
                    dp[i - 1][l - 1][(c + d - (a % d)) % d].map(|v| v + a),
                ]
                .iter()
                .flatten()
                .copied()
                .max();
            }
        }
    }

    let result = dp[n][k][0].map_or(-1, |v| v as isize);
    println!("{}", result);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc281/d/main.rs

%%%% begin
4 2 2
1 2 3 4
%%%%
6
%%%% end

%%%% begin
3 1 2
1 3 5
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
    for token in line.trim().split(" ") {
        let value: F = token
            .parse()
            .map_err(|e| io::Error::new(io::ErrorKind::Other, format!("{:?}", e)))?;
        result.push(value);
    }
    Ok(result)
}
