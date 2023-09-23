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
    let dfs = RecursiveClosure::new(|dfs, x: usize| {
        visited[x] = true;
        for &y in &adj[x] {
            if !visited[y] {
                dfs.call(y);
            }
        }
    });
    dfs.call(0);
    visited.iter().all(|&v| v)
}

fn main() {
    println!("{}", if main_solve() { "Yes" } else { "No" });
}

/*
python misc/run.py atcoder/abc287/c/main_v2.rs

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
// RecursiveClosure
//

struct RecursiveClosure<F> {
    inner: std::cell::RefCell<F>,
}

impl<F> RecursiveClosure<F> {
    fn new<Arg, Ret>(f: F) -> Self
    where
        F: FnMut(&dyn Callable<Arg, Ret>, Arg) -> Ret,
    {
        RecursiveClosure {
            inner: std::cell::RefCell::new(f),
        }
    }
}

trait Callable<Arg, Ret> {
    fn call(&self, arg: Arg) -> Ret;
}

impl<Arg, Ret, F> Callable<Arg, Ret> for RecursiveClosure<F>
where
    F: FnMut(&dyn Callable<Arg, Ret>, Arg) -> Ret,
{
    fn call(&self, arg: Arg) -> Ret {
        (unsafe { &mut *self.inner.as_ptr() })(self, arg)
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
