// AC

// https://atcoder.jp/contests/abc258/tasks/abc258_d

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let (n, x) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;
    let mut ls: Vec<(usize, usize)> = vec![];
    for _ in 0..n {
        ls.push(read_tokens().map(|v| (v[0], v[1]))?);
    }

    //
    // PROP.
    //  minimum sum takes the following form:
    //    (a1 + b1) + (a2 + b2) + ... + (ai + bi)
    //                                     + bi + ... + bi
    //

    let mut cumsum: Vec<usize> = vec![0; n + 1];
    for i in 0..n {
        cumsum[i + 1] = cumsum[i] + ls[i].0 + ls[i].1;
    }

    let mut result = std::usize::MAX;
    for i in 0..n {
        if x < i + 1 {
            break;
        }
        result = result.min(cumsum[i + 1] + ls[i].1 * (x - (i + 1)));
    }

    println!("{}", result);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc258/d/main.rs

%%%% begin
3 4
3 4
2 3
4 2
%%%%
18
%%%% end

%%%% begin
10 1000000000
3 3
1 6
4 7
1 8
5 7
9 9
2 4
6 4
5 1
3 1
%%%%
1000000076
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
