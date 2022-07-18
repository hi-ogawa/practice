// AC

use std::{fmt::Debug, io, str::FromStr};

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

fn main_case() -> io::Result<()> {
    let x: Vec<i64> = read_tokens()?;
    let x1: i64 = x[0];
    let y1: i64 = x[1];
    let x2: i64 = x[2];
    let y2: i64 = x[3];
    let x3: i64 = x[4];
    let y3: i64 = x[5];
    let a = x2 - x1;
    let b = y2 - y1;
    let c = x3 - x1;
    let d = y3 - y1;
    let det = a * d - b * c;
    let answer = match det.signum() {
        0 => "TOUCH",
        1 => "LEFT",
        -1 => "RIGHT",
        _ => unreachable!(),
    };
    println!("{}", answer);
    Ok(())
}

fn main() -> io::Result<()> {
    let t: usize = read_tokens()?[0];
    for _ in 0..t {
        main_case()?;
    }
    Ok(())
}

/*
python misc/run.py cses/geometry/task2189/main.rs

%%%% begin
3
1 1 5 3 2 3
1 1 5 3 4 1
1 1 5 3 3 2
%%%%
LEFT
RIGHT
TOUCH
%%%% end
*/
