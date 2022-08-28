// AC

// https://atcoder.jp/contests/abc266/tasks/abc266_c

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let mut ls: Vec<Vec<isize>> = vec![];
    for _ in 0..4 {
        ls.push(read_tokens()?);
    }

    for i in 0..4 {
        let p = &ls[i];
        let q = &ls[(i + 1) % 4];
        let r = &ls[(i + 2) % 4];
        let a = q[0] - p[0];
        let b = q[1] - p[1];
        let c = r[0] - p[0];
        let d = r[1] - p[1];
        if a * d - b * c <= 0 {
            println!("No");
            return Ok(());
        }
    }

    println!("Yes");
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc266/c/main.rs

%%%% begin
0 0
1 0
1 1
0 1
%%%%
Yes
%%%% end

%%%% begin
0 0
1 1
-1 0
1 -1
%%%%
No
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
