// AC

// https://atcoder.jp/contests/abc266/tasks/abc266_d

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let n: usize = read_tokens()?[0];
    let k: usize = 100_000 + 1;
    let mut ls: Vec<Vec<i64>> = vec![vec![0; 5]; k];
    for _ in 0..n {
        let (t, x, a) = read_tokens::<usize>().map(|v| (v[0], v[1], v[2]))?;
        ls[t][x] = a as i64;
    }

    let mut dp: Vec<Vec<i64>> = vec![vec![std::i64::MIN; 5]; k];
    dp[0][0] = 0;
    for i in 1..k {
        for j in 0..5 {
            let mut x = dp[i - 1][j];
            if j > 0 {
                x = x.max(dp[i - 1][j - 1]);
            }
            if j < 4 {
                x = x.max(dp[i - 1][j + 1]);
            }
            dp[i][j] = x + ls[i][j];
        }
    }

    let result = dp[k - 1].iter().max().unwrap();
    println!("{}", result);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc266/d/main.rs

%%%% begin
3
1 0 100
3 3 10
5 4 1
%%%%
101
%%%% end

%%%% begin
3
1 4 1
2 4 1
3 4 1
%%%%
0
%%%% end

%%%% begin
10
1 4 602436426
2 1 623690081
3 3 262703497
4 4 628894325
5 3 450968417
6 1 161735902
7 1 707723857
8 2 802329211
9 0 317063340
10 2 125660016
%%%%
2978279323
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
