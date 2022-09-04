// AC

// https://atcoder.jp/contests/abc267/tasks/abc267_c

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // n, m \in [1, 2 x 10^5]
    let (n, m): (usize, _) = read_tokens().map(|v| (v[0], v[1]))?;

    // a \in [-2 x 10^5, 2 x 10^5]
    let ls: Vec<isize> = read_tokens()?;

    let mut cumsum: Vec<isize> = vec![0; n + 1];
    for i in 0..n {
        cumsum[i + 1] = cumsum[i] + ls[i];
    }

    let mut current: isize = (0..m).map(|i| (i as isize + 1) * ls[i]).sum();
    let mut result = current;
    for k in m..n {
        current += -(cumsum[k] - cumsum[k - m]) + (m as isize) * ls[k];
        result = result.max(current);
    }
    println!("{}", result);

    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc267/c/main.rs

%%%% begin
4 2
5 4 -1 8
%%%%
15
%%%% end

%%%% begin
10 4
-3 1 -4 1 -5 9 -2 6 -5 3
%%%%
31
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
