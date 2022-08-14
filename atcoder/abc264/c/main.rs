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
    // comb(n, k) * comb(n, k) * n * n = 6350400 (n = 10, k = 5)
    let solve = || -> bool {
        for rows in Combinations::new(h1, h2) {
            for columns in Combinations::new(w1, w2) {
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

//
// iterate (n, k) combinations
//

struct Combinations {
    n: usize,
    s: Option<usize>,
}

impl Combinations {
    fn new(n: usize, k: usize) -> Self {
        assert!(k <= n);
        Self {
            n,
            s: Some((1 << k) - 1),
        }
    }

    fn compute_next(n: usize, s: usize) -> Option<usize> {
        // special case k = 0
        if s == 0 {
            return None;
        }

        // flip least significant "01" to "10"
        // keep the high bits
        // move all ones in low bits to trailing
        let next_one = ((s | (s - 1)) + 1).trailing_zeros() as usize;
        if next_one == n {
            return None;
        }
        let mask_lo: usize = (1 << (next_one - 1)) - 1;
        let mask_hi: usize = !((1 << (next_one + 1)) - 1);
        let low_ones: usize = (1 << (s & mask_lo).count_ones()) - 1;
        Some((s & mask_hi) | (1 << next_one) | low_ones)
    }
}

impl Iterator for Combinations {
    type Item = usize;

    fn next(&mut self) -> Option<Self::Item> {
        if let Some(s) = self.s {
            self.s = Combinations::compute_next(self.n, s);
            Some(s)
        } else {
            None
        }
    }
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
python misc/run.py atcoder/abc264/c/main.rs

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
    for token in line.trim().split(" ") {
        let value: F = token
            .parse()
            .map_err(|e| io::Error::new(io::ErrorKind::Other, format!("{:?}", e)))?;
        result.push(value);
    }
    Ok(result)
}
