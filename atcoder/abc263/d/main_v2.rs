// AC

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let (n, l, r) = read_tokens::<isize>().map(|v| (v[0] as usize, v[1], v[2]))?; // n \in [1, 2 x 10^5]
    let ls = read_tokens::<isize>()?; // [-10^9, 10^9]

    // dp(k) = min sum for applying l to ls[:k]
    let mut dp: Vec<isize> = vec![0; n + 1];
    for k in 0..n {
        dp[k + 1] = (dp[k] + ls[k]).min(((k as isize) + 1) * l);
    }

    let mut result = std::isize::MAX;
    for k in 0..=n {
        result = result.min(dp[k] + ((n as isize) - (k as isize)) * r);
    }

    println!("{}", result);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc263/d/main_v2.rs

%%%% begin
5 4 3
5 5 0 6 3
%%%%
14
%%%% end

%%%% begin
4 10 10
1 2 3 4
%%%%
10
%%%% end

%%%% begin
10 -5 -3
9 -6 10 -1 2 10 -1 7 -15 5
%%%%
-58
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
