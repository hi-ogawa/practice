// AC

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let (n, m) = read_tokens::<usize>().map(|v| (v[0], v[1]))?; // n \in (3, 100)
    let mut adj: Vec<Vec<bool>> = vec![vec![false; n]; n];
    for _ in 0..m {
        let (u, v) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;
        adj[u - 1][v - 1] = true;
        adj[v - 1][u - 1] = true;
    }

    // brute force
    let mut result: usize = 0;
    for i in 0..n {
        for j in (i + 1)..n {
            for k in (j + 1)..n {
                if adj[i][j] && adj[j][k] && adj[k][i] {
                    result += 1;
                }
            }
        }
    }

    println!("{}", result);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc262/b/main.rs

%%%% begin
5 6
1 5
4 5
2 3
1 4
3 5
2 5
%%%%
2
%%%% end

%%%% begin
3 1
1 2
%%%%
0
%%%% end

%%%% begin
7 10
1 7
5 7
2 5
3 6
4 7
1 5
2 4
1 3
1 6
2 7
%%%%
4
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
