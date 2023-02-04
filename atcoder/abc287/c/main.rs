// AC

// https://atcoder.jp/contests/abc287/tasks/abc287_c

fn main_solve() -> bool {
    // ~ 10^5
    // 2 <= n
    let (n, m) = {
        let v = read_tokens::<usize>();
        (v[0], v[1])
    };

    let mut adj: Vec<Vec<usize>> = vec![vec![]; n];
    for _ in 0..m {
        let mut v = read_tokens::<usize>();
        v[0] -= 1;
        v[1] -= 1;
        adj[v[0]].push(v[1]);
        adj[v[1]].push(v[0]);
    }

    // check tree
    if m != n - 1 {
        return false;
    }

    // check degree 1 or 2
    if !adj.iter().all(|edges| edges.len() <= 2) {
        return false;
    }

    // check connected
    let mut visited = vec![false; n];
    recursive_closure!(dfs, |x: usize| {
        visited[x] = true;
        for &y in &adj[x] {
            if !visited[y] {
                dfs(y);
            }
        }
    })(0);
    visited.iter().all(|&v| v)
}

fn main() {
    println!("{}", if main_solve() { "Yes" } else { "No" });
}

#[macro_export]
macro_rules! recursive_closure {
    ($N:ident, $E:expr) => {
        |x| {
            use std::cell::RefCell;

            struct Recurser<'a> {
                run: RefCell<&'a mut dyn FnMut(&Recurser, usize)>,
            }

            let mut recurser_impl = |recurser: &Recurser, x: usize| {
                let $N = |y: usize| (unsafe { &mut *recurser.run.as_ptr() })(recurser, y);
                $E(x)
            };

            let recurser = Recurser {
                run: RefCell::new(&mut recurser_impl),
            };

            (unsafe { &mut *recurser.run.as_ptr() })(&recurser, x)
        }
    };
}

/*
python misc/run.py atcoder/abc287/c/main.rs

%%%% begin
4 3
1 3
4 2
3 2
%%%%
Yes
%%%% end

%%%% begin
2 0
%%%%
No
%%%% end

%%%% begin
5 5
1 2
2 3
3 4
4 5
5 1
%%%%
No
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
