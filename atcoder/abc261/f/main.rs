// WIP

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let n: usize = read_tokens()?[0]; // [ 2, 3 x 10^5]
    let cs: Vec<usize> = read_tokens()?; // [1, n]
    let xs: Vec<usize> = read_tokens()?; // [1, n]

    //
    // answer = |{ (i, j) | i < j and Ci ≠ Cj and Xi > Xj } |
    //
    // ideas:
    // - compute color-by-color
    // - from right to left
    //

    let mut color_to_indices: Vec<Vec<usize>> = vec![vec![]; n + 1];
    for i in 0..n {
        color_to_indices[cs[i]].push(i);
    }

    // let mut counts: Vec<usize> = vec![0; n + 1];
    let mut result: usize = 0;

    for indices in color_to_indices.iter() {
        for i in indices.iter().rev() {
            // // number of same color on the right
            // let j = indices.len() - i - 1;
            // println!("{}", j);
            // result += 1;
        }
    }

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
python misc/run.py atcoder/abc261/f/main.rs

%%%% begin
5
1 5 2 2 1
3 2 1 2 1
%%%%
6
%%%% end

%%%% begin
3
1 1 1
3 2 1
%%%%
0
%%%% end

%%%% begin
3
3 1 2
1 1 2
%%%%
0
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
