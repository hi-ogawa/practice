// AC

// https://atcoder.jp/contests/abc257/tasks/abc257_c

use std::{collections::BTreeMap, fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let n: usize = read_tokens()?[0];
    let s: Vec<bool> = read_tokens::<String>()?[0]
        .chars()
        .map(|c| c == '1')
        .collect();
    let ws: Vec<usize> = read_tokens()?;

    // map[value] = indices
    let mut map: BTreeMap<usize, Vec<usize>> = BTreeMap::new();
    for i in 0..n {
        map.entry(ws[i]).or_default().push(i);
    }

    // initially w = 0
    let mut current = s.iter().filter(|&&b| b).count() as isize;
    let mut result = current;

    // increase w step by step
    for (_, indices) in map.iter() {
        current += indices
            .iter()
            .map(|&i| if s[i] { -1 } else { 1 })
            .sum::<isize>();
        result = result.max(current);
    }

    println!("{}", result);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc257/c/main.rs

%%%% begin
5
10101
60 45 30 40 80
%%%%
4
%%%% end

%%%% begin
3
000
1 2 3
%%%%
3
%%%% end

%%%% begin
5
10101
60 50 50 50 60
%%%%
4
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
