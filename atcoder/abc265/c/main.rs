// WIP

// https://atcoder.jp/contests/abc265/tasks/abc265_c

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let (n, m) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;
    let mut grid: Vec<Vec<char>> = vec![];
    for _ in 0..n {
        let line = read_tokens::<String>()?[0].clone();
        grid.push(line.chars().collect());
    }

    let (mut i, mut j) = (0, 0);
    let mut result: Option<(usize, usize)> = None;
    let mut visited: Vec<Vec<bool>> = vec![vec![false; m]; n];
    loop {
        if visited[i][j] {
            break;
        }
        visited[i][j] = true;
        match grid[i][j] {
            'D' => {
                if i + 1 == n {
                    result = Some((i, j));
                    break;
                }
                i += 1;
            }
            'U' => {
                if i == 0 {
                    result = Some((i, j));
                    break;
                }
                i -= 1;
            }
            'R' => {
                if j + 1 == m {
                    result = Some((i, j));
                    break;
                }
                j += 1;
            }
            'L' => {
                if j == 0 {
                    result = Some((i, j));
                    break;
                }
                j -= 1;
            }
            _ => unreachable!(),
        }
    }

    if let Some((i, j)) = result {
        println!("{} {}", i + 1, j + 1);
    } else {
        println!("-1");
    }
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc265/c/main.rs

%%%% begin
2 3
RDU
LRU
%%%%
1 3
%%%% end

%%%% begin
2 3
RRD
ULL
%%%%
-1
%%%% end

%%%% begin
9 44
RRDDDDRRRDDDRRRRRRDDDRDDDDRDDRDDDDDDRRDRRRRR
RRRDLRDRDLLLLRDRRLLLDDRDLLLRDDDLLLDRRLLLLLDD
DRDLRLDRDLRDRLDRLRDDLDDLRDRLDRLDDRLRRLRRRDRR
DDLRRDLDDLDDRLDDLDRDDRDDDDRLRRLRDDRRRLDRDRDD
RDLRRDLRDLLLLRRDLRDRRDRRRDLRDDLLLLDDDLLLLRDR
RDLLLLLRDLRDRLDDLDDRDRRDRLDRRRLDDDLDDDRDDLDR
RDLRRDLDDLRDRLRDLDDDLDDRLDRDRDLDRDLDDLRRDLRR
RDLDRRLDRLLLLDRDRLLLRDDLLLLLRDRLLLRRRRLLLDDR
RRRRDRDDRRRDDRDDDRRRDRDRDRDRRRRRRDDDRDDDDRRR
%%%%
9 5
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
