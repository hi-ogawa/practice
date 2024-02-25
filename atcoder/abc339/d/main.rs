// AC

// https://atcoder.jp/contests/abc339/tasks/abc339_d

use std::collections::VecDeque;

fn main() {
    // ~ 60
    let n: usize = read_vec()[0];
    let board: Vec<Vec<char>> = (0..n)
        .map(|_| read_vec::<String>()[0].chars().collect())
        .collect();

    // graph with
    // - (n^2)^2 (~ 10^7) vertices
    // - at most degree 4

    let mut init: Vec<[usize; 2]> = vec![];
    for i in 0..n {
        for j in 0..n {
            if board[i][j] == 'P' {
                init.push([i, j]);
            }
        }
    }
    type Node = [[usize; 2]; 2];
    let init: Node = [[init[0][0], init[0][1]], [init[1][0], init[1][1]]];

    let get_move = |[i, j]: [usize; 2], [di, dj]: [isize; 2]| -> [usize; 2] {
        let i2 = (i as isize + di).max(0).min(n as isize - 1) as usize;
        let j2 = (j as isize + dj).max(0).min(n as isize - 1) as usize;
        if board[i2][j2] != '#' {
            [i2, j2]
        } else {
            [i, j]
        }
    };

    let enc = |[[a, b], [c, d]]: Node| -> usize { a + n * (b + n * (c + n * d)) };

    // BFS
    let mut distances: Vec<Option<usize>> = vec![None; enc([[n; 2]; 2])];
    let mut queue: VecDeque<Node> = VecDeque::new();
    distances[enc(init)] = Some(0);
    queue.push_back(init);
    while let Some(v) = queue.pop_front() {
        if v[0] == v[1] {
            println!("{}", distances[enc(v)].unwrap());
            return;
        }
        for u in [[-1, 0], [1, 0], [0, -1], [0, 1]]
            .iter()
            .map(|&diff| [get_move(v[0], diff), get_move(v[1], diff)])
        {
            if distances[enc(u)].is_none() {
                distances[enc(u)] = Some(distances[enc(v)].unwrap() + 1);
                queue.push_back(u);
            }
        }
    }
    println!("{}", -1);
}

/*
python misc/run.py atcoder/abc339/d/main.rs

%%%% begin
5
....#
#..#.
.P...
..P..
....#
%%%%
3
%%%% end

%%%% begin
2
P#
#P
%%%%
-1
%%%% end

%%%% begin
10
..........
..........
..........
..........
....P.....
.....P....
..........
..........
..........
..........
%%%%
10
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
