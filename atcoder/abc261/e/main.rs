// AC

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let (n, c) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;
    let mut ls: Vec<(usize, usize)> = vec![(0, 0); n];
    for i in 0..n {
        ls[i] = read_tokens().map(|v| (v[0], v[1]))?;
    }

    // precompute each bit's result as
    //   0 --(after i steps)--> precomputed[i].0
    //   1 --(after i steps)--> precomputed[i].1
    let mut precomputed: Vec<(usize, usize)> = vec![(0, 0xffffffff); n + 1];

    for i in 0..n {
        let (t, a) = ls[i];
        match t {
            1 => {
                precomputed[i + 1] = (precomputed[i].0 & a, precomputed[i].1 & a);
            }
            2 => {
                precomputed[i + 1] = (precomputed[i].0 | a, precomputed[i].1 | a);
            }
            3 => {
                precomputed[i + 1] = (precomputed[i].0 ^ a, precomputed[i].1 ^ a);
            }
            _ => unreachable!(),
        }
    }

    // compute result
    let mut acc = c; // technically we don't need this since each bit doesn't affect other
    for i in 0..n {
        let mut result: usize = 0;
        for j in 0..30 {
            let pick = if (acc & (1 << j)) > 0 {
                precomputed[i + 1].1
            } else {
                precomputed[i + 1].0
            };
            result |= pick & (1 << j);
        }
        println!("{}", result);
        acc = result;
    }

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
python misc/run.py atcoder/abc261/e/main.rs

%%%% begin
3 10
3 3
2 5
1 12
%%%%
9
15
12
%%%% end

%%%% begin
9 12
1 1
2 2
3 3
1 4
2 5
3 6
1 7
2 8
3 9
%%%%
0
2
1
0
5
3
3
11
2
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
    for token in line.trim().split(' ') {
        let value: F = token
            .parse()
            .map_err(|e| io::Error::new(io::ErrorKind::Other, format!("{:?}", e)))?;
        result.push(value);
    }
    Ok(result)
}
