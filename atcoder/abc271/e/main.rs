// AC

// https://atcoder.jp/contests/abc271/tasks/abc271_e

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // ~ 10^5
    let (n, m, _k) = read_tokens::<usize>().map(|v| (v[0], v[1], v[2]))?;

    let mut edges: Vec<(usize, usize, usize)> = vec![];
    for _ in 0..m {
        edges.push(read_tokens::<usize>().map(|v| (v[0] - 1, v[1] - 1, v[2]))?);
    }

    let order = read_tokens::<usize>()?;

    let mut distances: Vec<Option<usize>> = vec![None; n];
    distances[0] = Some(0);
    for &i in &order {
        let (a, b, c) = edges[i - 1];
        if let Some(d) = distances[a] {
            distances[b] = Some(distances[b].unwrap_or(std::usize::MAX).min(c + d));
        }
    }

    let result = distances[n - 1].map(|v| v as isize).unwrap_or(-1);
    println!("{}", result);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc271/e/main.rs

%%%% begin
3 4 4
1 2 2
2 3 2
1 3 3
1 3 5
4 2 1 2
%%%%
4
%%%% end

%%%% begin
3 2 3
1 2 1
2 3 1
2 1 1
%%%%
-1
%%%% end

%%%% begin
4 4 5
3 2 2
1 3 5
2 4 7
3 4 10
2 4 1 4 3
%%%%
14
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
