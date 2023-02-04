// TLE

/*
it looks okay locally

$ time ./build/main < atcoder/abc262/d/data/in.txt
794961497

real    0m1,885s
user    0m1,686s
sys     0m0,197s
 */

use std::{fmt::Debug, io, str::FromStr};

const MODULO: usize = 998244353;

fn main_case() -> io::Result<()> {
    let n: usize = read_tokens()?[0]; // [1, 100]
    let ls: Vec<usize> = read_tokens()?; // [1, 10^9]

    // dp[i][j][k][l] = #{ S | S ⊆ {a1, ..., ai} and ∑S % l = j and |S| = k }
    let mut dp = vec![vec![vec![vec![0usize; n + 1]; n + 1]; n]; n + 1];
    for l in 1..=n {
        dp[0][0][0][l] = 1;
    }
    for i in 0..n {
        for j in 0..n {
            for k in 0..n {
                for l in 1..=n {
                    dp[i + 1][j][k][l] += dp[i][j][k][l];
                    dp[i + 1][j][k][l] %= MODULO;
                    dp[i + 1][(j + ls[i]) % l][k + 1][l] += dp[i][j][k][l];
                    dp[i + 1][(j + ls[i]) % l][k + 1][l] %= MODULO;
                }
            }
        }
    }

    let result = (1..=n).map(|l| dp[n][0][l][l]).sum::<usize>() % MODULO;
    println!("{}", result);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc262/d/main.rs

%%%% begin
3
2 6 2
%%%%
6
%%%% end

%%%% begin
5
5 5 5 5 5
%%%%
31
%%%% end
*/

//
// utils
//

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
