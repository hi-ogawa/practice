// WA

// https://atcoder.jp/contests/abc280/tasks/abc280_d

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // k \in [2, 10^12]
    let k: usize = read_tokens()?[0];

    // factorize
    let factors = factorize(k);
    assert!(factors.len() > 0);
    // dbg!(&factors);

    // solve for each factor and take maximum
    let mut result: usize = 0;
    for &(p, e) in &factors {
        // find min { x | e ≤ 1 + ... + x }
        let x = lower_bound(0, e, |x| e <= (1 + x) * x / 2);
        dbg!(p, e, 2);
        result = result.max(p.pow(x as u32));
    }

    println!("{}", result);
    Ok(())
}

//
// prime factorizatoin
//

fn factorize(mut n: usize) -> Vec<(usize, usize)> {
    let mut result: Vec<(usize, usize)> = vec![];

    for p in 2.. {
        if p * p > n {
            break;
        }
        let mut e = 0;
        while n % p == 0 {
            n /= p;
            e += 1;
        }
        if e > 0 {
            result.push((p, e));
        }
    }

    if n > 1 {
        result.push((n, 1));
    }

    result
}

//
// binary search
//

fn lower_bound<F: Fn(usize) -> bool>(mut x0: usize, mut x1: usize, f: F) -> usize {
    assert!(!f(x0));
    assert!(f(x1));
    while x0 + 1 < x1 {
        let x = (x0 + x1 + 1) / 2;
        if f(x) {
            x1 = x;
        } else {
            x0 = x;
        }
    }
    x1
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc280/d/main_v1.rs

%%%% begin
9
%%%%
6
%%%% end

%%%% begin
30
%%%%
5
%%%% end

%%%% begin
123456789011
%%%%
123456789011
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
