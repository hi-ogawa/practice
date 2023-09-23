// AC

// https://atcoder.jp/contests/abc308/tasks/abc308_d

use std::collections::VecDeque;

fn main() {
    let [h, w] = read_array();
    let ls: Vec<Vec<char>> = (0..h)
        .map(|_| read_vec::<String>()[0].chars().collect())
        .collect();

    // reachability when available edges are simply
    //   s -> n
    //   n -> u
    //   u -> k
    //   k -> e
    //   e -> s
    // note that, only because there's no duplicate character,
    // we can solve in "context-free" manner.
    // otherwise, we would need to differentiate (vertex, character-index) state.

    if ls[0][0] != 's' {
        println!("No");
        return;
    }

    let goods: Vec<(char, char)> = "snuke".chars().zip("nukes".chars()).collect();

    let mut queue: VecDeque<(usize, usize)> = VecDeque::new();
    let mut visited: Vec<Vec<bool>> = vec![vec![false; w]; h];
    let mut ok = false;
    queue.push_back((0, 0));
    visited[0][0] = true;
    while let Some(v) = queue.pop_front() {
        if v == (h - 1, w - 1) {
            ok = true;
            break;
        }
        for &u in grid_adj(v.0, v.1, h, w).iter().flatten() {
            if visited[u.0][u.1] {
                continue;
            }
            if goods.contains(&(ls[v.0][v.1], ls[u.0][u.1])) {
                queue.push_back(u);
                visited[u.0][u.1] = true;
            }
        }
    }
    println!("{}", if ok { "Yes" } else { "No" });
}

fn grid_adj(i: usize, j: usize, h: usize, w: usize) -> [Option<(usize, usize)>; 4] {
    let mut adj = [None; 4];
    if i > 0 {
        adj[0] = Some((i - 1, j));
    }
    if i < h - 1 {
        adj[1] = Some((i + 1, j));
    }
    if j > 0 {
        adj[2] = Some((i, j - 1));
    }
    if j < w - 1 {
        adj[3] = Some((i, j + 1));
    }
    adj
}

/*
python misc/run.py atcoder/abc308/d/main.rs

%%%% begin
2 3
sns
euk
%%%%
Yes
%%%% end

%%%% begin
2 2
ab
cd
%%%%
No
%%%% end

%%%% begin
5 7
skunsek
nukesnu
ukeseku
nsnnesn
uekukku
%%%%
Yes
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
    use std::convert::TryInto;
    read_vec::<T>().try_into().ok().unwrap()
}
