// WIP

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
    // let t: usize = read_tokens()?[0];
    // for _ in 0..t {
    //     main_case()?
    // }
    // Ok(())
}

/*
python misc/run.py {{FILE}}

{{TESTS}}
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
