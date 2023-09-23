// AC

// https://atcoder.jp/contests/abc288/tasks/abc288_c

fn main() {
    let (n, m) = {
        let v: Vec<usize> = read_tokens();
        (v[0], v[1])
    };

    let mut adj: Vec<Vec<usize>> = vec![vec![]; n];
    for _ in 0..m {
        let v: Vec<usize> = read_tokens();
        adj[v[0] - 1].push(v[1] - 1);
        adj[v[1] - 1].push(v[0] - 1);
    }

    // DFS to count back edges
    let mut num_back_edges = 0;
    let mut visited = vec![false; n];
    let dfs = RecursiveClosure::new(|dfs, x: usize| {
        if visited[x] {
            return;
        }
        visited[x] = true;
        for &y in &adj[x] {
            if visited[y] {
                num_back_edges += 1;
                continue;
            }
            dfs.call(y);
        }
    });
    for x in 0..n {
        dfs.call(x);
    }

    // subtract by DFS tree edges
    num_back_edges -= m;
    println!("{}", num_back_edges);
}

/*
python misc/run.py atcoder/abc288/c/main.rs

%%%% begin
6 7
1 2
1 3
2 3
4 2
6 5
4 6
4 5
%%%%
2
%%%% end

%%%% begin
4 2
1 2
3 4
%%%%
0
%%%% end

%%%% begin
5 3
1 2
1 3
2 3
%%%%
1
%%%% end
*/

//
// recursive closure
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
