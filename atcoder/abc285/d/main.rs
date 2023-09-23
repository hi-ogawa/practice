// AC

// https://atcoder.jp/contests/abc285/tasks/abc285_d

use std::collections::HashMap;

fn main_case() {
    // ~ 10^5
    let n: usize = read_tokens()[0];
    let mut pairs: Vec<(String, String)> = vec![];
    for _ in 0..n {
        pairs.push({
            let v: Vec<String> = read_tokens();
            (v[0].clone(), v[1].clone())
        });
    }

    // define directional edge (i, j) \iff t_i = s_j
    let mut edges: HashMap<&String, (Option<usize>, Option<usize>)> = HashMap::new();
    for (i, pair) in pairs.iter().enumerate() {
        edges.entry(&pair.0).or_default().0 = Some(i);
        edges.entry(&pair.1).or_default().1 = Some(i);
    }

    // degree is at most one due to "pairwise distinct" constraints
    let mut adj: Vec<Option<usize>> = vec![None; n];
    for pair in edges.values() {
        if let Some(x) = pair.1 {
            if let Some(y) = pair.0 {
                assert!(adj[x] == None);
                adj[x] = Some(y);
            }
        }
    }

    // DFS (solvable \iff DAG (i.e. no loop))
    struct Dfs {
        n: usize,
        adj: Vec<Option<usize>>,
        visited: Vec<bool>,
        entered: Vec<bool>,
    }

    impl Dfs {
        fn new(adj: Vec<Option<usize>>) -> Self {
            let n = adj.len();
            Self {
                n,
                adj,
                visited: vec![false; n],
                entered: vec![false; n],
            }
        }

        fn solve(&mut self) -> Option<()> {
            for root in 0..self.n {
                if !self.visited[root] {
                    self.solve_rec(root)?
                }
            }
            Some(())
        }

        fn solve_rec(&mut self, x: usize) -> Option<()> {
            self.visited[x] = true;
            self.entered[x] = true;
            if let Some(y) = self.adj[x] {
                if self.entered[y] {
                    return None;
                }
                if !self.visited[y] {
                    self.solve_rec(y)?;
                }
            }
            self.entered[x] = false;
            Some(())
        }
    }

    let result = Dfs::new(adj).solve();
    let result = if result.is_some() { "Yes" } else { "No" };
    println!("{}", result);
}

fn main() {
    main_case();
}

/*
python misc/run.py atcoder/abc285/d/main.rs

%%%% begin
2
b m
m d
%%%%
Yes
%%%% end

%%%% begin
3
a b
b c
c a
%%%%
No
%%%% end

%%%% begin
5
aaa bbb
yyy zzz
ccc ddd
xxx yyy
bbb ccc
%%%%
Yes
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
