// AC

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let v: Vec<isize> = read_tokens()?;

    // let sup_norm = v[0].abs_diff(8).max(v[1].abs_diff(8));
    let sup_norm = (v[0] - 8).abs().max((v[1] - 8).abs()); // rust 1.42.0

    let result = if sup_norm % 2 == 0 { "white" } else { "black" };
    println!("{}", result);

    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc264/b/main.rs

%%%% begin
3 5
%%%%
black
%%%% end

%%%% begin
4 5
%%%%
white
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
