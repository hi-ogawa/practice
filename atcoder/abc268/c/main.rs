// AC

// https://atcoder.jp/contests/abc268/tasks/abc268_c

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let n: usize = read_tokens()?[0];
    let ls: Vec<usize> = read_tokens()?;

    // accumulate how much rotation is required to match the permutatoin for each index
    let mut shifts: Vec<usize> = vec![0; n];
    for (i, &x) in ls.iter().enumerate() {
        shifts[(n + x - i) % n] += 1;
    }

    let result = (0..n)
        .map(|i| shifts[i] + shifts[(i + 1) % n] + shifts[(i + 2) % n])
        .max()
        .unwrap();
    println!("{}", result);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc268/c/main.rs

%%%% begin
4
1 2 0 3
%%%%
4
%%%% end

%%%% begin
3
0 1 2
%%%%
3
%%%% end

%%%% begin
10
3 9 6 1 7 2 8 0 5 4
%%%%
5
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
