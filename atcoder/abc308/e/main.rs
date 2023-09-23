// AC

// https://atcoder.jp/contests/abc308/tasks/abc308_e

fn main() {
    // ~ 10^5
    let n: usize = read_vec()[0];
    // 0, 1, 2
    let ls: Vec<usize> = read_vec();
    // M, E, X
    let s: Vec<char> = read_vec::<String>()[0].chars().collect();

    // count the number of "X" at the right (grouped by 0, 1, 2)
    let mut xs: Vec<Vec<usize>> = vec![vec![0; 3]; n];
    for i in (0..n - 1).rev() {
        for a in 0..3 {
            xs[i][a] = xs[i + 1][a];
            if s[i + 1] == 'X' && ls[i + 1] == a {
                xs[i][a] += 1
            }
        }
    }

    // count the number "EX" at the right (grouped by (0, 0), (0, 1), ...)
    let mut exs: Vec<Vec<Vec<usize>>> = vec![vec![vec![0; 3]; 3]; n];
    for i in (0..n - 1).rev() {
        for a in 0..3 {
            for b in 0..3 {
                exs[i][a][b] = exs[i + 1][a][b];
                if s[i + 1] == 'E' && ls[i + 1] == a {
                    exs[i][a][b] += xs[i + 1][b];
                }
            }
        }
    }

    // count all "MEX" grouped by (0, 0, 0), (0, 0, 1), ...
    let mut mexs: Vec<Vec<Vec<usize>>> = vec![vec![vec![0; 3]; 3]; 3];
    for i in 0..n {
        if s[i] == 'M' {
            for a in 0..3 {
                for b in 0..3 {
                    mexs[ls[i]][a][b] += exs[i][a][b];
                }
            }
        }
    }

    // compute MEX and aggregate
    let mut result = 0;
    for a in 0..3 {
        for b in 0..3 {
            for c in 0..3 {
                result += mexs[a][b][c] * get_mex(&mut [a, b, c].iter().copied());
            }
        }
    }
    println!("{}", result);
}

fn get_mex(iter: &mut dyn Iterator<Item = usize>) -> usize {
    let mut exists = [false; 4];
    for x in iter {
        exists[x] = true;
    }
    for a in 0.. {
        if !exists[a] {
            return a;
        }
    }
    unreachable!()
}

/*
python misc/run.py atcoder/abc308/e/main.rs

%%%% begin
4
1 1 0 2
MEEX
%%%%
3
%%%% end

%%%% begin
3
0 0 0
XXX
%%%%
0
%%%% end

%%%% begin
15
1 1 2 0 0 2 0 2 0 0 0 0 0 2 2
EXMMXXXEMEXEXMM
%%%%
13
%%%% end
*/

//
// utils
//

#[allow(dead_code)]
fn read_vec<T: std::str::FromStr>() -> Vec<T> {
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).unwrap();
    line.split_whitespace()
        .map(|s| s.parse().ok().unwrap())
        .collect()
}

#[allow(dead_code)]
fn read_array<T: std::str::FromStr, const LEN: usize>() -> [T; LEN] {
    #[allow(unused_imports)]
    use std::convert::TryInto;
    read_vec::<T>().try_into().ok().unwrap()
}
