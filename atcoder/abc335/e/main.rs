// AC

// https://atcoder.jp/contests/abc335/tasks/abc335_e

use std::collections::{HashMap, HashSet};

fn main() {
    // 10^5
    let [n, m]: [usize; 2] = read_array();
    let ls: Vec<usize> = read_vec();
    let edges: Vec<[usize; 2]> = (0..m)
        .map(|_| read_array::<usize, 2>())
        .map(|[i, j]| [i - 1, j - 1])
        .collect();

    //
    // quotient graph (DAG of strongly connected components)
    //
    let mut dsu = Dsu::new(n);
    for &[i, j] in &edges {
        if ls[i] == ls[j] {
            dsu.merge(i, j);
        }
    }
    let verts: HashSet<usize> = (0..n).map(|u| dsu.find(u)).collect();
    let verts_map: HashMap<usize, usize> = verts.iter().enumerate().map(|(i, &v)| (v, i)).collect();
    let n2 = verts_map.len();
    let mut adj2: Vec<Vec<usize>> = vec![vec![]; n2];
    for &[mut i, mut j] in &edges {
        if ls[i] == ls[j] {
            continue;
        }
        if ls[i] > ls[j] {
            [i, j] = [j, i];
        }
        let i2 = verts_map[&dsu.find(i)];
        let j2 = verts_map[&dsu.find(j)];
        adj2[i2].push(j2);
    }

    //
    // topological sort + DP to find longest path
    //
    let v_start = verts_map[&dsu.find(0)];
    let v_end = verts_map[&dsu.find(n - 1)];
    let mut visited: Vec<bool> = vec![false; n];
    let mut order: Vec<usize> = vec![];
    let dfs = RecursiveClosure::new(|dfs, x: usize| {
        visited[x] = true;
        for &y in &adj2[x] {
            if !visited[y] {
                dfs.call(y);
            }
        }
        order.push(x);
    });
    dfs.call(v_start);

    // check if reachable
    if !visited[v_end] {
        println!("{}", 0);
        return;
    }

    // dp(i) = length of longest path to reach "i"
    let mut dp: Vec<usize> = vec![0; n2];
    for &i in order.iter().rev() {
        for &j in &adj2[i] {
            dp[j] = dp[j].max(dp[i] + 1);
        }
    }
    println!("{}", dp[v_end] + 1);
}

/*
python misc/run.py atcoder/abc335/e/main.rs

%%%% begin
5 6
10 20 30 40 50
1 2
1 3
2 5
3 4
3 5
4 5
%%%%
4
%%%% end

%%%% begin
4 5
1 10 11 4
1 2
1 3
2 3
2 4
3 4
%%%%
0
%%%% end

%%%% begin
10 12
1 2 3 3 4 4 4 6 5 7
1 3
2 9
3 4
5 6
1 2
8 9
4 5
8 10
7 10
4 6
2 8
6 7
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
// disjoint set union
//

struct Dsu {
    parents: Vec<usize>,
}

impl Dsu {
    fn new(n: usize) -> Self {
        Self {
            parents: (0..n).collect(),
        }
    }

    fn find(&mut self, x: usize) -> usize {
        let mut p = self.parents[x];
        if p != x {
            p = self.find(p);
            self.parents[x] = p;
        }
        p
    }

    fn merge(&mut self, mut dst: usize, mut src: usize) {
        dst = self.find(dst);
        src = self.find(src);
        self.parents[src] = dst;
    }
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
