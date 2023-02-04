// AC

// https://atcoder.jp/contests/abc276/tasks/abc276_d

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // n ~ 10^3
    let _n: usize = read_tokens()?[0];
    // a ~ 10^9
    let ls: Vec<usize> = read_tokens()?;

    // factorize(x) = (p, q, r)  \iff  x = r 2^p 3^q where 2 ∤ r and 3 ∤ r
    fn factorize(mut x: usize) -> (usize, usize, usize) {
        let mut p = 0;
        let mut q = 0;
        while x % 2 == 0 {
            x /= 2;
            p += 1;
        }
        while x % 3 == 0 {
            x /= 3;
            q += 1;
        }
        (p, q, x)
    }
    let factors: Vec<(usize, usize, usize)> = ls.iter().map(|&x| factorize(x)).collect();

    // solvable all "r" are same
    let r = factors[0].2;
    if !factors.iter().all(|f| f.2 == r) {
        println!("-1");
        return Ok(());
    }

    // maximize common factors
    let p = factors.iter().map(|f| f.0).min().unwrap();
    let q = factors.iter().map(|f| f.1).min().unwrap();
    let result = factors.iter().map(|f| f.0 - p).sum::<usize>()
        + factors.iter().map(|f| f.1 - q).sum::<usize>();
    println!("{}", result);

    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc276/d/main.rs

%%%% begin
3
1 4 3
%%%%
3
%%%% end

%%%% begin
3
2 7 6
%%%%
-1
%%%% end

%%%% begin
6
1 1 1 1 1 1
%%%%
0
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
