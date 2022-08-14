// AC

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let s = read_tokens::<String>()?[0].clone();
    let n = s.len();

    // find each target index
    let mut ls: Vec<usize> = vec![0; n];
    for (i, c) in s.chars().enumerate() {
        ls[i] = "atcoder".match_indices(c).next().unwrap().0;
    }

    // count inversions
    let mut result: usize = 0;
    for i in 0..n {
        for j in (i + 1)..n {
            if ls[i] > ls[j] {
                result += 1;
            }
        }
    }

    println!("{}", result);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc264/d/main.rs

%%%% begin
catredo
%%%%
8
%%%% end

%%%% begin
atcoder
%%%%
0
%%%% end

%%%% begin
redocta
%%%%
21
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
