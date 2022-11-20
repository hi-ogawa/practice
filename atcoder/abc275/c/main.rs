// AC

// https://atcoder.jp/contests/abc275/tasks/abc275_c

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let n: usize = 9;

    let mut board: Vec<Vec<bool>> = vec![];
    for _ in 0..n {
        let tokens = read_tokens::<String>()?;
        board.push(tokens[0].chars().map(|c| c == '#').collect());
    }

    let make_turn = |(x1, y1): (isize, isize), (x2, y2): (isize, isize)| -> (isize, isize) {
        let dx = x2 - x1;
        let dy = y2 - y1;
        (x2 - dy, y2 + dx)
    };

    let make_square =
        |p: (isize, isize), q: (isize, isize)| -> Option<((isize, isize), (isize, isize))> {
            let r = make_turn(p, q);
            let s = make_turn(q, r);
            if [r.0, r.1, s.0, s.1]
                .iter()
                .all(|&x| 0 <= x && x < n as isize)
            {
                Some((r, s))
            } else {
                None
            }
        };

    let positions: Vec<(isize, isize)> = (0..n)
        .flat_map(|i| (0..n).map(move |j| (i as isize, j as isize)))
        .collect();

    let mut result: usize = 0;

    // enumerate squares by picking two points
    for &p in &positions {
        for &q in &positions {
            if p == q {
                continue;
            }
            // derive square
            if let Some((r, s)) = make_square(p, q) {
                // check board
                if [p, q, r, s]
                    .iter()
                    .all(|&(x, y)| board[x as usize][y as usize])
                {
                    result += 1;
                }
            }
        }
    }

    // resolve duplicate counts
    result /= 4;
    println!("{}", result);
    Ok(())
}

// funct

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc275/c/main.rs

%%%% begin
##.......
##.......
.........
.......#.
.....#...
........#
......#..
.........
.........
%%%%
2
%%%% end

%%%% begin
.#.......
#.#......
.#.......
.........
....#.#.#
.........
....#.#.#
........#
.........
%%%%
3
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
