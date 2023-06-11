// AC

// https://atcoder.jp/contests/abc301/tasks/abc301_e

use std::collections::VecDeque;

fn main() {
    // h, w ~ 10^3
    // t ~ 10^6
    let (h, w, t) = {
        let v: Vec<usize> = read_tokens();
        (v[0], v[1], v[2])
    };

    let mut board: Vec<Vec<char>> = vec![];
    for _ in 0..h {
        board.push(read_tokens::<String>()[0].chars().collect());
    }

    //
    // collect special coordinates
    //
    let mut start = None;
    let mut goal = None;
    let mut candies = vec![];
    for i in 0..h {
        for j in 0..w {
            match board[i][j] {
                'S' => {
                    start = Some((i, j));
                }
                'G' => {
                    goal = Some((i, j));
                }
                'o' => {
                    candies.push((i, j));
                }
                _ => {}
            }
        }
    }
    let start = start.unwrap();
    let goal = goal.unwrap();
    let k = candies.len();

    //
    // compute distance between "start", "goal" and candies
    //
    let get_neighbors = |(i, j): (usize, usize)| -> Vec<(usize, usize)> {
        let mut result: Vec<(usize, usize)> = vec![];
        if i > 0 {
            result.push((i - 1, j));
        }
        if i + 1 < h {
            result.push((i + 1, j));
        }
        if j > 0 {
            result.push((i, j - 1));
        }
        if j + 1 < w {
            result.push((i, j + 1));
        }
        result
    };

    let dfs = |root: (usize, usize)| -> Vec<Vec<Option<usize>>> {
        let mut dist = vec![vec![None; w]; h];
        let mut queue: VecDeque<(usize, usize)> = VecDeque::new();
        dist[root.0][root.1] = Some(0);
        queue.push_back(root);
        while let Some(v) = queue.pop_front() {
            for u in get_neighbors(v) {
                if board[u.0][u.1] != '#' && dist[u.0][u.1] == None {
                    dist[u.0][u.1] = Some(dist[v.0][v.1].unwrap() + 1);
                    queue.push_back(u);
                }
            }
        }
        dist
    };

    let d_start = dfs(start);
    let d_goal = dfs(goal);
    let d_candies: Vec<Vec<Vec<Option<usize>>>> = candies.iter().map(|&c| dfs(c)).collect();

    // check reachable
    match d_start[goal.0][goal.1] {
        Some(d) if d <= t => {}
        _ => {
            println!("-1");
            return;
        }
    }

    //
    // solve dp(Xs, x) = (min steps to collect Xs (set of candies) and end at x (candy))
    //
    let mut dp: Vec<Vec<Option<usize>>> = vec![vec![None; k]; 1 << k];

    for (i, &c) in candies.iter().enumerate() {
        dp[1 << i][i] = d_start[c.0][c.1];
    }

    for s in 0..(1 << k) {
        for i in 0..k {
            if s & (1 << i) == 0 {
                continue;
            }
            for j in 0..k {
                if s & (1 << j) > 0 {
                    continue;
                }
                let c = candies[j];
                match (dp[s][i], d_candies[i][c.0][c.1]) {
                    (Some(d1), Some(d2)) => {
                        dp[s | (1 << j)][j] =
                            Some(dp[s | (1 << j)][j].unwrap_or(std::usize::MAX).min(d1 + d2))
                    }
                    _ => {}
                }
            }
        }
    }

    //
    // find maximum
    //
    let mut result = 0;
    for s in 0..(1 << k) {
        for i in 0..k {
            let c = candies[i];
            match (dp[s][i], d_goal[c.0][c.1]) {
                (Some(d1), Some(d2)) => {
                    // TODO: we can already filter out during dp
                    if d1 + d2 <= t {
                        result = result.max(s.count_ones());
                    }
                }
                _ => {}
            }
        }
    }
    println!("{}", result);
}

/*
python misc/run.py atcoder/abc301/e/main.rs

%%%% begin
3 3 5
S.G
o#o
.#.
%%%%
1
%%%% end

%%%% begin
3 3 1
S.G
.#o
o#.
%%%%
-1
%%%% end

%%%% begin
5 10 2000000
S.o..ooo..
..o..o.o..
..o..ooo..
..o..o.o..
..o..ooo.G
%%%%
18
%%%% end

*/

//
// utils
//

#[allow(dead_code)]
fn read_tokens<T: std::str::FromStr>() -> Vec<T>
where
    <T as std::str::FromStr>::Err: std::fmt::Debug,
{
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).unwrap();
    line.split_whitespace()
        .map(|s| s.parse().unwrap())
        .collect()
}
