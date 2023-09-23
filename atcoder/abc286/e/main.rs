// AC

// https://atcoder.jp/contests/abc286/tasks/abc286_e

use std::collections::BTreeSet;

fn main() {
    // n ~ 300
    let n: usize = read_tokens()[0];
    let ls: Vec<usize> = read_tokens();

    let mut adj: Vec<Vec<usize>> = vec![vec![]; n];
    for i in 0..n {
        for (j, c) in read_tokens::<String>()[0].chars().enumerate() {
            if c == 'Y' {
                adj[i].push(j);
            }
        }
    }

    //
    // BFS x n times
    //

    let solve = |s: usize| -> Vec<Option<(usize, usize)>> {
        let mut dp: Vec<Option<(usize, usize)>> = vec![None; n];
        let mut queue: BTreeSet<(usize, isize, usize)> = BTreeSet::new(); // (distance, -reward, vertex)
        queue.insert((0, -(ls[s] as isize), s));
        while let Some((distance, neg_reward, x)) = pop_first(&mut queue) {
            if dp[x].is_some() {
                continue;
            }
            dp[x] = Some((distance, (-neg_reward) as usize));
            for &y in &adj[x] {
                if dp[y].is_none() {
                    queue.insert((distance + 1, neg_reward - (ls[y] as isize), y));
                }
            }
        }
        dp
    };

    let result: Vec<Vec<Option<(usize, usize)>>> = (0..n).map(move |x| solve(x)).collect();

    //
    // answer queries
    //
    let num_q: usize = read_tokens()[0];
    for _ in 0..num_q {
        let v: Vec<usize> = read_tokens();
        match result[v[0] - 1][v[1] - 1] {
            Some(r) => {
                println!("{} {}", r.0, r.1);
            }
            None => {
                println!("Impossible");
            }
        }
    }
}

/*
python misc/run.py atcoder/abc286/e/main.rs

%%%% begin
5
30 50 70 20 60
NYYNN
NNYNN
NNNYY
YNNNN
YNNNN
3
1 3
3 1
4 5
%%%%
1 100
2 160
3 180
%%%% end

%%%% begin
2
100 100
NN
NN
1
1 2
%%%%
Impossible
%%%% end
*/

// old rust compat
fn pop_first<T: std::cmp::Ord + Copy>(queue: &mut BTreeSet<T>) -> Option<T> {
    if let Some(&e) = queue.iter().next() {
        queue.remove(&e);
        Some(e)
    } else {
        None
    }
}

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
