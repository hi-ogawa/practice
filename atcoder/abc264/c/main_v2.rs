// AC

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let (h1, w1) = read_tokens::<usize>().map(|v| (v[0], v[1]))?; // ~ 10
    let mut a_grid: Vec<Vec<usize>> = vec![];
    for _ in 0..h1 {
        a_grid.push(read_tokens()?);
    }

    let (h2, w2) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;
    let mut b_grid: Vec<Vec<usize>> = vec![];
    for _ in 0..h2 {
        b_grid.push(read_tokens()?);
    }

    // brute force
    let solve = || -> bool {
        for rows in 0..(1usize << h1) {
            if rows.count_ones() as usize != h2 {
                continue;
            }
            for columns in 0..(1usize << w1) {
                if columns.count_ones() as usize != w2 {
                    continue;
                }
                let solve_inner = || -> bool {
                    for (i2, i1) in BitIterator(rows).enumerate() {
                        for (j2, j1) in BitIterator(columns).enumerate() {
                            if a_grid[i1][j1] != b_grid[i2][j2] {
                                return false;
                            }
                        }
                    }
                    true
                };
                if solve_inner() {
                    // dbg!((to_bin(rows, h1), to_bin(columns, w1)));
                    return true;
                }
            }
        }
        false
    };

    let result = if solve() { "Yes" } else { "No" };
    println!("{}", result);
    Ok(())
}

#[allow(dead_code)]
fn to_bin(s: usize, n: usize) -> String {
    (0..n)
        .rev()
        .map(|i| ((s >> i) & 1).to_string())
        .collect::<Vec<_>>()
        .join("")
}

//
// iterate bits
//

struct BitIterator(usize);

impl Iterator for BitIterator {
    type Item = usize;

    fn next(&mut self) -> Option<Self::Item> {
        let x = self.0;
        if x == 0 {
            return None;
        }
        self.0 = x & (x - 1);
        Some(x.trailing_zeros() as usize)
    }
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc264/c/main_v2.rs

%%%% begin
4 5
1 2 3 4 5
6 7 8 9 10
11 12 13 14 15
16 17 18 19 20
2 3
6 8 9
16 18 19
%%%%
Yes
%%%% end

%%%% begin
3 3
1 1 1
1 1 1
1 1 1
1 1
2
%%%%
No
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
