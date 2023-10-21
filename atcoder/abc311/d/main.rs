// AC

// https://atcoder.jp/contests/abc311/tasks/abc311_d

use std::{collections::VecDeque, fmt::Display};

fn main() {
    // ~ 200
    let [n, m]: [usize; 2] = read_array();
    let board: Vec<Vec<char>> = (0..n)
        .map(|_| read_vec::<String>()[0].chars().collect())
        .collect();

    // pre-compute edges
    let mut adj: Vec<Vec<Vec<[usize; 2]>>> = vec![vec![vec![]; m]; n];

    // right/left moves for each row
    for i in 0..n {
        // right
        let mut block = m - 1;
        for j in (0..m).rev() {
            match board[i][j] {
                '.' => {
                    adj[i][j].push([i, block - 1]);
                }
                '#' => {
                    block = j;
                }
                _ => unreachable!(),
            }
        }

        // left
        let mut block = 0;
        for j in 0..m {
            match board[i][j] {
                '.' => {
                    adj[i][j].push([i, block + 1]);
                }
                '#' => {
                    block = j;
                }
                _ => unreachable!(),
            }
        }
    }

    // up/down moves for each column
    for j in 0..m {
        // down
        let mut block = n - 1;
        for i in (0..n).rev() {
            match board[i][j] {
                '.' => {
                    adj[i][j].push([block - 1, j]);
                }
                '#' => {
                    block = i;
                }
                _ => unreachable!(),
            }
        }

        // up
        let mut block = 0;
        for i in 0..n {
            match board[i][j] {
                '.' => {
                    adj[i][j].push([block + 1, j]);
                }
                '#' => {
                    block = i;
                }
                _ => unreachable!(),
            }
        }
    }

    // BFS
    let mut visited: Vec<Vec<bool>> = vec![vec![false; m]; n];
    let mut queue: VecDeque<[usize; 2]> = VecDeque::new();
    visited[1][1] = true;
    queue.push_back([1, 1]);
    while let Some([i, j]) = queue.pop_front() {
        for &[a, b] in &adj[i][j] {
            if !visited[a][b] {
                visited[a][b] = true;
                queue.push_back([a, b]);
            }
        }
    }

    // collect all "passing" squares from "rest-on" square
    // O(n^2 (4n)) ~ O(n^3)
    let mut passed: Vec<Vec<bool>> = vec![vec![false; m]; n];
    for i in 0..n {
        for j in 0..m {
            if visited[i][j] {
                for &[a, b] in &adj[i][j] {
                    if a == i {
                        let range = if j < b { j..=b } else { b..=j };
                        for c in range {
                            passed[i][c] = true;
                        }
                    }
                    if b == j {
                        let range = if i < a { i..=a } else { a..=i };
                        for c in range {
                            passed[c][j] = true;
                        }
                    }
                }
            }
        }
    }

    eprintln!("== rest-on\n{}", DebugVec2 { data: &visited });
    eprintln!("== passing\n{}", DebugVec2 { data: &passed });

    struct DebugVec2<'a> {
        data: &'a Vec<Vec<bool>>,
    }

    impl<'a> Display for DebugVec2<'a> {
        fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
            for row in self.data {
                for &b in row {
                    write!(f, "{}", if b { '.' } else { '#' })?;
                }
                writeln!(f)?
            }
            Ok(())
        }
    }

    let result: usize = passed
        .iter()
        .map(|row| row.iter().filter(|&&b| b).count())
        .sum();
    println!("{}", result);
}

/*
python misc/run.py atcoder/abc311/d/main.rs

%%%% begin
6 6
######
#....#
#.#..#
#..#.#
#....#
######
%%%%
12
%%%% end

%%%% begin
21 25
#########################
#..............###...####
#..............#..#...###
#........###...#...#...##
#........#..#..#........#
#...##...#..#..#...#....#
#..#..#..###...#..#.....#
#..#..#..#..#..###......#
#..####..#..#...........#
#..#..#..###............#
#..#..#.................#
#........##.............#
#.......#..#............#
#..........#....#.......#
#........###...##....#..#
#..........#..#.#...##..#
#.......#..#....#..#.#..#
##.......##.....#....#..#
###.............#....#..#
####.................#..#
#########################
%%%%
215
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
