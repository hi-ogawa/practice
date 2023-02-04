// AC

// https://atcoder.jp/contests/abc259/tasks/abc259_e

use std::{collections::BTreeMap, fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let n: usize = read_tokens()?[0];

    let mut ls: Vec<Vec<(usize, usize)>> = vec![vec![]; n];
    for i in 0..n {
        let m: usize = read_tokens()?[0];
        for _ in 0..m {
            let (p, e) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;
            ls[i].push((p, e));
        }
    }

    // p => e => count
    let mut counts: BTreeMap<usize, BTreeMap<usize, usize>> = BTreeMap::new();
    for x in &ls {
        for &(p, e) in x {
            *counts
                .entry(p)
                .or_insert(BTreeMap::new())
                .entry(e)
                .or_insert(0) += 1;
        }
    }

    // check how many uniquely attains max exponent
    let mut result = 1;
    for x in &ls {
        for &(p, e) in x {
            let (&e_max, &count) = counts[&p].iter().rev().next().unwrap();
            if e == e_max && count == 1 {
                // dbg!(x);
                result += 1;
                break;
            }
        }
    }

    // adjust special case
    result = result.min(n);

    println!("{}", result);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc259/e/main.rs

%%%% begin
4
1
7 2
2
2 2
5 1
1
5 1
2
2 1
7 1
%%%%
3
%%%% end

%%%% begin
1
1
998244353 1000000000
%%%%
1
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
