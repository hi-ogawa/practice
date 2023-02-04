// AC

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let n: usize = read_tokens()?[0]; // n \in [2, 5 x 10^5]
    let ls: Vec<usize> = read_tokens()?; // \in [1, n]

    // 1-based index for simplicity
    let ls: Vec<usize> = vec![0].into_iter().chain(ls.into_iter()).collect();

    //   i-th  .... j-th
    //    (i)        (j)   --- 1st case
    //    (j)        (i)   --- 2nd case

    // 1st case
    let count_matches: usize = (1..=n).map(|i| i == ls[i]).map(usize::from).sum();
    let result1 = count_matches * (count_matches - 1) / 2;

    // 2nd case
    let result2: usize = (1..=n)
        .map(|i| i < ls[i] && ls[ls[i]] == i)
        .map(usize::from)
        .sum();

    let result = result1 + result2;
    println!("{}", result);
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
python misc/run.py atcoder/abc262/c/main.rs

%%%% begin
4
1 3 2 4
%%%%
2
%%%% end

%%%% begin
10
5 8 2 2 1 6 7 2 9 10
%%%%
8
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
