// AC

// https://atcoder.jp/contests/abc257/tasks/abc257_e

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let n: usize = read_tokens()?[0];
    let cs: Vec<usize> = (0..1).chain(read_tokens()?.into_iter()).collect(); // for simplicity, prepend 0

    // optimize the number of trials
    let i_min = (1..10).min_by_key(|&i| cs[i]).unwrap();
    let c_min = cs[i_min];
    let k = n / c_min;

    // greedily replace i_min with 9, 8, ...
    let mut budget = n - k * c_min;
    let mut counts: Vec<usize> = vec![0; 10];
    counts[i_min] = k;
    for _ in 0..k {
        for i in ((i_min + 1)..10).rev() {
            let cost = cs[i] - c_min;
            if cost <= budget {
                budget -= cost;
                counts[i] += 1;
                counts[i_min] -= 1;
                break;
            }
        }
    }

    // construct results
    let result = (1..10)
        .rev()
        .map(|i| i.to_string().repeat(counts[i]))
        .collect::<Vec<_>>()
        .join("");
    println!("{}", result);

    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc257/e/main.rs

%%%% begin
5
5 4 3 3 2 5 3 5 3
%%%%
95
%%%% end

%%%% begin
20
1 1 1 1 1 1 1 1 1
%%%%
99999999999999999999
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
