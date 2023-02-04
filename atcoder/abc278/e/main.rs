// AC

// https://atcoder.jp/contests/abc278/tasks/abc278_e

use std::{collections::HashMap, fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // ~ 300
    let (h1, w1, _n, h, w) = read_tokens::<usize>().map(|v| (v[0], v[1], v[2], v[3], v[4]))?;
    let mut board: Vec<Vec<usize>> = vec![];
    for _ in 0..h1 {
        board.push(read_tokens()?);
    }

    let mut counts: HashMap<usize, usize> = HashMap::new();
    for i in 0..h1 {
        for j in 0..w1 {
            *counts.entry(board[i][j]).or_default() += 1;
        }
    }

    // brute force
    let mut current = counts.clone();

    for k in 0..(h1 - h + 1) {
        for i in k..k + h {
            for j in 0..w {
                *current.entry(board[i][j]).or_default() -= 1;
                if current.get(&board[i][j]) == Some(&0) {
                    current.remove(&board[i][j]);
                }
            }
        }
        print!("{}", current.len());

        for l in 0..(w1 - w) {
            for i in k..k + h {
                *current.entry(board[i][l]).or_default() += 1;
                *current.entry(board[i][l + w]).or_default() -= 1;
                if current.get(&board[i][l + w]) == Some(&0) {
                    current.remove(&board[i][l + w]);
                }
            }
            print!(" {}", current.len());
        }
        println!();

        current = counts.clone();
    }

    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc278/e/main.rs

%%%% begin
3 4 5 2 2
2 2 1 1
3 2 5 3
3 4 4 3
%%%%
4 4 3
5 3 4
%%%% end

%%%% begin
5 6 9 3 4
7 1 5 3 9 5
4 5 4 5 1 2
6 1 6 2 9 7
4 7 1 5 8 8
3 4 3 3 5 3
%%%%
8 8 7
8 9 7
8 9 8
%%%% end

%%%% begin
9 12 30 4 7
2 2 2 2 2 2 2 2 2 2 2 2
2 2 20 20 2 2 5 9 10 9 9 23
2 29 29 29 29 29 28 28 26 26 26 15
2 29 29 29 29 29 25 25 26 26 26 15
2 29 29 29 29 29 25 25 8 25 15 15
2 18 18 18 18 1 27 27 25 25 16 16
2 19 22 1 1 1 7 3 7 7 7 7
2 19 22 22 6 6 21 21 21 7 7 7
2 19 22 22 22 22 21 21 21 24 24 24
%%%%
21 20 19 20 18 17
20 19 18 19 17 15
21 19 20 19 18 16
21 19 19 18 19 18
20 18 18 18 19 18
18 16 17 18 19 17
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
