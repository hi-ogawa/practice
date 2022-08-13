// AC

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let (n, m) = read_tokens::<usize>().map(|v| (v[0], v[1]))?; // 1 <= m <= n <= 5000
    let x_vec: Vec<isize> = read_tokens()?; // [1, 10^9]
    let mut bonuses: Vec<isize> = vec![0; n + 1];
    for _ in 0..m {
        let (c, y) = read_tokens::<usize>().map(|v| (v[0], v[1]))?; // c \in [1, n]
        bonuses[c] = y as isize;
    }

    // dp(i, c) = max scores up to i-th trial with couter c
    let mut dp: Vec<Vec<isize>> = vec![vec![std::isize::MIN; n + 1]; n + 1];
    dp[0][0] = 0;

    for i in 0..n {
        for c in 0..n {
            dp[i + 1][c + 1] = dp[i][c] + x_vec[i] + bonuses[c + 1];
            dp[i + 1][0] = dp[i + 1][0].max(dp[i][c]);
        }
    }

    let mut result = std::isize::MIN;
    for &x in dp[n].iter() {
        result = result.max(x);
    }
    println!("{}", result);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc261/d/main.rs

%%%% begin
6 3
2 7 1 8 2 8
2 10
3 1
5 5
%%%%
48
%%%% end

%%%% begin
3 2
1000000000 1000000000 1000000000
1 1000000000
3 1000000000
%%%%
5000000000
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
    for token in line.trim().split(" ") {
        let value: F = token
            .parse()
            .map_err(|e| io::Error::new(io::ErrorKind::Other, format!("{:?}", e)))?;
        result.push(value);
    }
    Ok(result)
}
