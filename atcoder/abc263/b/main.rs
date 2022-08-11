// WIP

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let n = read_tokens::<usize>()?[0];
    let ls = read_tokens::<usize>()?;

    // normalize
    let mut ls: Vec<_> = ls.iter().map(|x| x - 1).collect();
    ls.splice(0..0, vec![0]);

    let mut x = n - 1;
    let mut result = 0;
    while x != 0 {
        x = ls[x];
        result += 1;
    }
    println!("{}", result);

    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc263/b/main.rs

%%%% begin
3
1 2
%%%%
2
%%%% end

%%%% begin
10
1 2 3 4 5 6 7 8 9
%%%%
9
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
