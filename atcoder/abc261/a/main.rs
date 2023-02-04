// AC

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let vec: Vec<i64> = read_tokens()?;
    let l0 = vec[0];
    let r0 = vec[1];
    let l1 = vec[2];
    let r1 = vec[3];
    let result = (r0.min(r1) - l0.max(l1)).max(0);
    println!("{}", result);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc261/a/main.rs

%%%% begin
0 3 1 5
%%%%
2
%%%% end

%%%% begin
0 1 4 5
%%%%
0
%%%% end

%%%% begin
0 3 3 7
%%%%
0
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
