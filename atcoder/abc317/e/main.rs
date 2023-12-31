// AC

// https://atcoder.jp/contests/abc317/tasks/abc317_e

use std::collections::VecDeque;

fn main() {
    // ~ 2000
    let [h, w]: [usize; 2] = read_array();
    let mut board: Vec<Vec<char>> = (0..h)
        .map(|_| read_vec::<String>()[0].chars().collect())
        .collect();

    // find start/goal
    let mut start: [usize; 2] = [0, 0];
    let mut goal: [usize; 2] = [0, 0];
    for i in 0..h {
        for j in 0..w {
            match board[i][j] {
                'S' => {
                    start = [i, j];
                    board[i][j] = '.';
                }
                'G' => {
                    goal = [i, j];
                    board[i][j] = '.';
                }
                _ => {}
            }
        }
    }

    // solve line of sight
    let mut passable: Vec<Vec<bool>> = vec![vec![true; w]; h];
    for i in 0..h {
        let mut ok = true;
        for j in 0..w {
            match board[i][j] {
                '.' => {
                    passable[i][j] = passable[i][j] & ok;
                }
                '>' => {
                    passable[i][j] = false;
                    ok = false;
                }
                _ => {
                    passable[i][j] = false;
                    ok = true;
                }
            }
        }
    }
    for i in 0..h {
        let mut ok = true;
        for j in (0..w).rev() {
            match board[i][j] {
                '.' => {
                    passable[i][j] = passable[i][j] & ok;
                }
                '<' => {
                    passable[i][j] = false;
                    ok = false;
                }
                _ => {
                    passable[i][j] = false;
                    ok = true;
                }
            }
        }
    }
    for j in 0..w {
        let mut ok = true;
        for i in 0..h {
            match board[i][j] {
                '.' => {
                    passable[i][j] = passable[i][j] & ok;
                }
                'v' => {
                    passable[i][j] = false;
                    ok = false;
                }
                _ => {
                    passable[i][j] = false;
                    ok = true;
                }
            }
        }
    }
    for j in 0..w {
        let mut ok = true;
        for i in (0..h).rev() {
            match board[i][j] {
                '.' => {
                    passable[i][j] = passable[i][j] & ok;
                }
                '^' => {
                    passable[i][j] = false;
                    ok = false;
                }
                _ => {
                    passable[i][j] = false;
                    ok = true;
                }
            }
        }
    }

    // BFS
    let mut distance: Vec<Vec<Option<usize>>> = vec![vec![None; w]; h];
    let mut queue: VecDeque<[usize; 2]> = VecDeque::new();
    distance[start[0]][start[1]] = Some(0);
    queue.push_back(start);
    while let Some(v) = queue.pop_front() {
        if v == goal {
            break;
        }
        for u in adj_iterator(v, [h, w]) {
            if !passable[u[0]][u[1]] {
                continue;
            }
            if distance[u[0]][u[1]].is_some() {
                continue;
            }
            distance[u[0]][u[1]] = Some(distance[v[0]][v[1]].unwrap() + 1);
            queue.push_back(u);
        }
    }

    if let Some(u) = distance[goal[0]][goal[1]] {
        println!("{}", u);
    } else {
        println!("-1");
    }
}

fn adj_iterator([x, y]: [usize; 2], [h, w]: [usize; 2]) -> impl Iterator<Item = [usize; 2]> {
    let mut v: Vec<[usize; 2]> = vec![];
    if x > 0 {
        v.push([x - 1, y]);
    }
    if x < h - 1 {
        v.push([x + 1, y]);
    }
    if y > 0 {
        v.push([x, y - 1]);
    }
    if y < w - 1 {
        v.push([x, y + 1]);
    }
    v.into_iter()
}

/*
python misc/run.py atcoder/abc317/e/main.rs

%%%% begin
5 7
....Sv.
.>.....
.......
>..<.#<
^G....>
%%%%
15
%%%% end

%%%% begin
4 3
S..
.<.
.>.
..G
%%%%
-1
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
