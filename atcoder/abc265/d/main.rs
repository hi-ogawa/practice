// AC

// https://atcoder.jp/contests/abc265/tasks/abc265_d

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let (n, p, q, r) = read_tokens::<usize>().map(|v| (v[0], v[1], v[2], v[3]))?;
    let ls: Vec<usize> = read_tokens()?;

    let mut results: Vec<Vec<bool>> = vec![vec![false; n]; 3];
    solve(&ls, &mut results[0], p);
    solve(&ls, &mut results[1], p + q);
    solve(&ls, &mut results[2], p + q + r);

    for i in 0..n {
        if (0..3).all(|j| results[j][i]) {
            println!("Yes");
            return Ok(());
        }
    }
    println!("No");
    Ok(())
}

fn solve(ls: &Vec<usize>, result: &mut Vec<bool>, target: usize) {
    assert!(target > 0);
    let mut l: usize = 0;
    let mut r: usize = 0;
    let mut s: usize = 0;
    while r <= ls.len() {
        if s == target {
            result[l] = true;
            s -= ls[l];
            l += 1;
            continue;
        }
        if s > target {
            s -= ls[l];
            l += 1;
            continue;
        }
        if s < target {
            if r < ls.len() {
                s += ls[r];
            }
            r += 1;
            continue;
        }
    }
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc265/d/main.rs

%%%% begin
10 5 7 5
1 3 2 2 2 3 1 4 3 2
%%%%
Yes
%%%% end

%%%% begin
9 100 101 100
31 41 59 26 53 58 97 93 23
%%%%
No
%%%% end

%%%% begin
7 1 1 1
1 1 1 1 1 1 1
%%%%
Yes
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
