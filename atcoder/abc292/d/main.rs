// AC

// https://atcoder.jp/contests/abc292/tasks/abc292_d

fn main() {
    // ~ 10^5
    let (n, m) = {
        let v: Vec<usize> = read_tokens();
        (v[0], v[1])
    };

    // not necessary "simple" graph (i.e. multiple edges betweeen two vertices)
    let mut adj: Vec<Vec<usize>> = vec![vec![]; n];
    for _ in 0..m {
        let v: Vec<usize> = read_tokens();
        adj[v[0] - 1].push(v[1] - 1);
        adj[v[1] - 1].push(v[0] - 1);
    }

    // PROP.
    //  connected graph with |vertices| = |edges|
    //    \iff
    //  DFS finds single back edge

    let mut visited = vec![false; n];
    let mut components = vec![[0, 0]; n]; // (num vertices, num back edges)

    let dfs = RecursiveClosure::new(|dfs, (root, x): (usize, usize)| {
        if visited[x] {
            return;
        }
        components[root][0] += 1;
        visited[x] = true;
        for &y in &adj[x] {
            if visited[y] {
                components[root][1] += 1;
                continue;
            }
            dfs.call((root, y));
        }
    });

    for x in 0..n {
        dfs.call((x, x));
    }

    let mut result = true;
    for &[v, e] in &components {
        // if tree, e = v - 1
        if v > 0 && e != v + 1 {
            result = false;
        }
    }
    println!("{}", if result { "Yes" } else { "No" });
}

/*
python misc/run.py atcoder/abc292/d/main.rs

%%%% begin
3 3
2 3
1 1
2 3
%%%%
Yes
%%%% end

%%%% begin
5 5
1 2
2 3
3 4
3 5
1 5
%%%%
Yes
%%%% end

%%%% begin
13 16
7 9
7 11
3 8
1 13
11 11
6 11
8 13
2 11
3 3
8 12
9 11
1 11
5 13
3 12
6 9
1 10
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
