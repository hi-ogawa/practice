use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // k \in [2, 10^12]
    let k: usize = read_tokens()?[0];

    let gcd = |mut x: usize, mut y: usize| -> usize {
        if x < y {
            (x, y) = (y, x);
        }
        while y > 0 {
            (x, y) = (y, x % y);
        }
        x
    };

    let check = |mut k: usize, n: usize| -> bool {
        for x in 2..=n {
            k /= gcd(x, k);
        }
        k == 1
    };

    for n in 2.. {
        if check(k, n) {
            println!("{}", n);
            break;
        }
    }
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc280/d/brute.rs

%%%% begin
30
%%%%
5
%%%% end

%%%% begin
280
%%%%
7
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
