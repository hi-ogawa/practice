// AC

// https://atcoder.jp/contests/abc285/tasks/abc285_d

// experimenting with recursive mutable clousure in rust

use std::{cell::RefCell, collections::HashMap};

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
    let mut visited = vec![false; n];
    let mut entered = vec![false; n];

    struct Dfs<'a> {
        run: RefCell<&'a mut dyn FnMut(&Dfs, usize) -> Option<()>>,
    }

    let mut dfs_impl = |dfs: &Dfs, x: usize| -> Option<()> {
        if visited[x] {
            return Some(());
        }
        visited[x] = true;
        entered[x] = true;
        for &y in &adj[x] {
            if entered[y] {
                return None;
            }
            if !visited[y] {
                // TODO
                // thread 'main' panicked at 'already borrowed: BorrowMutError', atcoder/abc285/d/main_v2.rs:58:17
                // (dfs.run.borrow_mut())(dfs, y)?

                // TODO: is this undefined behavior?
                // - https://doc.rust-lang.org/std/cell/
                // - https://doc.rust-lang.org/std/cell/struct.UnsafeCell.html
                (unsafe { &mut *dfs.run.as_ptr() })(dfs, y)?
            }
        }
        entered[x] = false;
        Some(())
    };

    let dfs = Dfs {
        run: RefCell::new(&mut dfs_impl),
    };

    let result = (0..n)
        // CE https://atcoder.jp/contests/abc285/submissions/38588270
        // .map(|x| (dfs.run.borrow_mut())(&dfs, x))
        .map(|x| (unsafe { &mut *dfs.run.as_ptr() })(&dfs, x))
        .all(|x| x.is_some());

    println!("{}", if result { "Yes" } else { "No" });
}

fn main() {
    main_case();
}

/*
python misc/run.py atcoder/abc285/d/main_v2.rs

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
