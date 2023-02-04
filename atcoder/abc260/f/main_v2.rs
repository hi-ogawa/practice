// AFTER EDITORIAL

// https://atcoder.jp/contests/abc260/tasks/abc260_f

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let (s, t, m) = read_tokens::<usize>().map(|v| (v[0], v[1], v[2]))?; // s ∈ [2, 3x 10^5], t ∈ [2, 3000]
    let n = s + t;

    // adjacency list from S to T
    let mut adj: Vec<Vec<usize>> = vec![vec![]; n + 1];
    for _ in 0..m {
        let (x, y) = read_tokens::<usize>().map(|v| (v[0] - 1, v[1] - s - 1))?;
        adj[x].push(y);
    }

    //
    // brute force by O(t^2) by pigeon hole principle
    //

    let mut acc: Vec<Vec<Option<usize>>> = vec![vec![None; t]; t];
    for x in 0..s {
        let k = adj[x].len();
        for i in 0..k {
            for j in (i + 1)..k {
                let y = adj[x][i];
                let z = adj[x][j];
                match acc[y][z] {
                    Some(w) => {
                        println!("{} {} {} {}", x + 1, y + s + 1, w + 1, z + s + 1);
                        return Ok(());
                    }
                    None => {
                        acc[y][z] = Some(x);
                        acc[z][y] = Some(x);
                    }
                }
            }
        }
    }
    println!("-1");
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc260/f/main_v2.rs

%%%% begin
2 3 5
1 3
1 4
1 5
2 4
2 5
%%%%
1 2 4 5
%%%% end

%%%% begin
3 2 4
1 4
1 5
2 5
3 5
%%%%
-1
%%%% end

%%%% begin
4 5 9
3 5
1 8
3 7
1 9
4 6
2 7
4 8
1 7
2 9
%%%%
1 7 2 9
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
    for token in line.trim().split(' ') {
        let value: F = token
            .parse()
            .map_err(|e| io::Error::new(io::ErrorKind::Other, format!("{:?}", e)))?;
        result.push(value);
    }
    Ok(result)
}
