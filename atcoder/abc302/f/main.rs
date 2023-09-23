// AC

// https://atcoder.jp/contests/abc302/tasks/abc302_f

use std::collections::{BTreeSet, VecDeque};

fn main() {
    // n, m ~ 10^5
    let v: Vec<usize> = read_tokens();
    let (n, m) = (v[0], v[1]);

    let mut sets: Vec<BTreeSet<usize>> = vec![];
    for _ in 0..n {
        let _a: usize = read_tokens()[0];
        let v: Vec<usize> = read_tokens();
        sets.push(v.iter().copied().collect());
    }

    // hyper edge for sets sharing the same number
    let mut edges: Vec<Vec<usize>> = vec![vec![]; m + 1];
    for (i, set) in sets.iter().enumerate() {
        for &x in set {
            edges[x].push(i);
        }
    }

    // BFS
    let mut dist: Vec<Option<usize>> = vec![None; n];
    let mut queue: VecDeque<usize> = VecDeque::new();
    {
        let init = 1;
        for &i in &edges[init] {
            dist[i] = Some(0);
            queue.push_back(i);
            sets[i].remove(&init);
        }
    }
    while let Some(i) = queue.pop_front() {
        for x in sets[i].clone() {
            for &j in &edges[x] {
                sets[j].remove(&x); // TODO: does it affect complexity?
                if let None = dist[j] {
                    dist[j] = Some(dist[i].unwrap() + 1);
                    queue.push_back(j);
                }
            }
        }
    }

    let result = edges[m].iter().flat_map(|&i| dist[i]).min();
    if let Some(result) = result {
        println!("{}", result);
    } else {
        println!("-1");
    }
}

/*
python misc/run.py atcoder/abc302/f/main.rs

%%%% begin
3 5
2
1 2
2
2 3
3
3 4 5
%%%%
2
%%%% end

%%%% begin
1 2
2
1 2
%%%%
0
%%%% end

%%%% begin
3 5
2
1 3
2
2 4
3
2 4 5
%%%%
-1
%%%% end

%%%% begin
4 8
3
1 3 5
2
1 2
3
2 4 7
4
4 6 7 8
%%%%
2
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
