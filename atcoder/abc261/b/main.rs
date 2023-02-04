// AC

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let n: usize = read_tokens()?[0];
    let board: Vec<Vec<char>> = (0..n)
        .map(|_| read_tokens::<String>().unwrap()[0].chars().collect())
        .collect();
    for i in 0..n {
        for j in (i + 1)..n {
            match (board[i][j], board[j][i]) {
                ('W', 'L') | ('L', 'W') | ('D', 'D') => {}
                _ => {
                    println!("incorrect");
                    return Ok(());
                }
            }
        }
    }
    println!("correct");
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc261/b/main.rs

%%%% begin
4
-WWW
L-DD
LD-W
LDW-
%%%%
incorrect
%%%% end

%%%% begin
2
-D
D-
%%%%
correct
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
