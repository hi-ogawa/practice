// AC

// https://atcoder.jp/contests/abc282/tasks/abc282_f

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // [1, 4000]
    let n: usize = read_tokens()?[0];

    //
    // enumerate all power-of-2 length intervals
    //   n x log2(n) = 4000 x log2(4000) < 4000 x 12 = 48000
    //

    let k_max = (n as f64).log2().ceil() as usize + 1;
    let mut intervals: Vec<Vec<(usize, usize)>> = vec![vec![]; k_max];
    for k in 0..k_max {
        for l in 1.. {
            let r = l + (1 << k) - 1;
            if r > n {
                break;
            }
            intervals[k].push((l, r));
        }
    }

    let mut len_cumsum: Vec<usize> = vec![0; k_max + 1];
    for k in 0..k_max {
        len_cumsum[k + 1] = len_cumsum[k] + intervals[k].len();
    }

    let m = len_cumsum[k_max];
    println!("{}", m);

    for k in 0..k_max {
        for &(l, r) in &intervals[k] {
            println!("{} {}", l, r);
        }
    }

    //
    // answer queries
    //

    // [1, 10^5]
    let q: usize = read_tokens()?[0];
    for _ in 0..q {
        let (ql, qr) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;
        let x = qr + 1 - ql;
        let k = (x as f64).log2().floor() as usize;
        let a = len_cumsum[k] + ql - 1;
        let b = len_cumsum[k] + qr - (1 << k);
        println!("{} {}", a + 1, b + 1);
    }

    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc282/f/main.rs

%%%% begin
4
4
1 3
3 4
2 4
1 1
%%%%
8
1 1
2 2
3 3
4 4
1 2
2 3
3 4
1 4
5 6
7 7
6 7
1 1
%%%% end

%%%% begin
4
1
1 4
%%%%
8
1 1
2 2
3 3
4 4
1 2
2 3
3 4
1 4
8 8
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
