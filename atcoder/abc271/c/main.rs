// WA

// https://atcoder.jp/contests/abc271/tasks/abc271_c

use std::{collections::VecDeque, fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let _n: usize = read_tokens()?[0]; // 3 x 10^5

    let mut ls: Vec<usize> = read_tokens()?; // [1, 10^9]
    ls.sort();

    let mut ls: VecDeque<usize> = ls.into_iter().collect();

    let mut result = 0;
    while let Some(&k) = ls.get(0) {
        if k != result + 1 {
            if ls.len() < 2 {
                break;
            }
            ls.pop_back();
            ls.pop_back();
            ls.push_front(result + 1);
        }
        ls.pop_front();
        result += 1;
    }
    println!("{}", result);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc271/c/main.rs

%%%% begin
6
1 2 4 6 7 271
%%%%
4
%%%% end

%%%% begin
10
1 1 1 1 1 1 1 1 1 1
%%%%
5
%%%% end

%%%% begin
1
5
%%%%
0
%%%% end

// counter example
%%%% begin
4
1 1 1 3
%%%%
3
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
