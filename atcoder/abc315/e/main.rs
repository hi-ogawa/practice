// AC

// https://atcoder.jp/contests/abc315/tasks/abc315_e

fn main() {
    // n ~ 10^5
    let n: usize = read_vec()[0];

    // #(edges) ~ 10^5
    let mut adj: Vec<Vec<usize>> = vec![vec![]; n];

    for i in 0..n {
        for j in &read_vec::<usize>()[1..] {
            adj[i].push(j - 1);
        }
    }
    // dbg!(&adj);

    // - collect reachable from root
    // - order by DFS "exit time" (topological sort)

    let mut visited = vec![false; n];
    let mut order: Vec<usize> = vec![];
    let dfs = RecursiveClosure::new(|dfs, x: usize| {
        visited[x] = true;
        for &y in &adj[x] {
            if !visited[y] {
                dfs.call(y);
            }
        }
        order.push(x);
    });
    dfs.call(0);

    assert!(order.pop() == Some(0));
    println!(
        "{}",
        order
            .iter()
            .map(|i| (i + 1).to_string())
            .collect::<Vec<_>>()
            .join(" ")
    );
}

/*
python misc/run.py atcoder/abc315/e/main.rs

%%%% begin
6
3 2 3 4
2 3 5
0
1 5
0
0
%%%%
5 3 4 2
%%%% end

%%%% begin
6
1 2
1 3
1 4
1 5
1 6
0
%%%%
6 5 4 3 2
%%%% end

%%%% begin
8
1 5
1 6
1 7
1 8
0
0
0
0
%%%%
5
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

//
// recursive closure without macro
//
struct RecursiveClosure<F>(std::cell::RefCell<F>);

impl<F> RecursiveClosure<F> {
    fn new<Arg, Ret>(f: F) -> Self
    where
        F: FnMut(&dyn Callable<Arg, Ret>, Arg) -> Ret,
    {
        RecursiveClosure(std::cell::RefCell::new(f))
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
        (unsafe { &mut *self.0.as_ptr() })(self, arg)
    }
}
