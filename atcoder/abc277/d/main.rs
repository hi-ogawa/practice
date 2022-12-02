// WA

// https://atcoder.jp/contests/abc277/tasks/abc277_d

use std::{collections::BTreeMap, fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // n ~ 10^5
    // m ~ 10^9
    let (_n, m) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;

    // x \in [0, m)
    let ls: Vec<usize> = read_tokens()?;

    let mut count_map: BTreeMap<usize, usize> = BTreeMap::new();
    for &x in &ls {
        *count_map.entry(x).or_default() += 1;
    }
    let mut counts: Vec<(usize, usize)> = count_map.into_iter().collect();
    counts.sort();

    // split to segments
    let mut segments: Vec<Vec<(usize, usize)>> = vec![];
    segments.push(vec![counts[0]]);

    for (&(x, _), &(y, cy)) in counts.iter().zip(&counts[1..]) {
        if x + 1 == y {
            segments.last_mut().unwrap().push((y, cy));
        } else {
            segments.push(vec![(y, cy)]);
        }
    }

    // concat first and last
    if segments.len() >= 2 && ls[0] == 0 && *ls.last().unwrap() == m - 1 {
        let last = segments.pop().unwrap();
        segments[0].extend(last);
    }

    // take segment with max sum
    let best: usize = segments
        .iter()
        .map(|s| s.iter().map(|&(x, cx)| x * cx).sum())
        .max()
        .unwrap();
    let total: usize = ls.iter().sum();
    let result = total - best;
    println!("{}", result);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc277/d/main.rs

%%%% begin
9 7
3 0 2 5 5 3 0 6 3
%%%%
11
%%%% end

%%%% begin
1 10
4
%%%%
0
%%%% end

%%%% begin
20 20
18 16 15 9 8 8 17 1 3 17 11 9 12 11 7 3 2 14 3 12
%%%%
99
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
