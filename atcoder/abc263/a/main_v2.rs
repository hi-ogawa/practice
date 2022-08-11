// WIP

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let mut ls = read_tokens::<usize>()?;

    ls.sort();
    let c1 = ls.iter().filter(|&&z| z == ls[0]).count();
    let c2 = ls.iter().filter(|&&z| z == ls[4]).count();

    match (c1, c2) {
        (2, 3) | (3, 2) => println!("Yes"),
        _ => println!("No"),
    }

    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc263/a/main_v2.rs

%%%% begin
1 2 1 2 1
%%%%
Yes
%%%% end

%%%% begin
12 12 11 1 2
%%%%
No
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
