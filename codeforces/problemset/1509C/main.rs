// WIP

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let n: usize = read_tokens()?[0]; // [1, 2000]
    let mut ls: Vec<usize> = read_tokens()?; // [1, 10^9]
    ls.sort();

    let mut m = n;
    for i in 0..n {
        let x = ls[i];
        for j in (i + 1)..m {
            let y = ls[j];

            ls.swap(i, j);
            m = j;
            break;
        }
    }
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py codeforces/problemset/1509C/main.rs

%%%% begin
3
3 1 2
%%%%
3
%%%% end

%%%% begin
1
5
%%%%
0
%%%% end

%%%% begin
6
1 6 3 3 6 3
%%%%
11
%%%% end

%%%% begin
6
104 943872923 6589 889921234 1000000000 69
%%%%
2833800505
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
