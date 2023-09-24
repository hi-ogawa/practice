// AC

// https://atcoder.jp/contests/abc309/tasks/abc309_e

fn main() {
    // ~ 10^5
    let [n, m]: [usize; 2] = read_array();
    let to_parent: Vec<usize> = read_vec();
    let insurances: Vec<[usize; 2]> = (0..m).map(|_| read_array()).collect();

    let mut adj: Vec<Vec<usize>> = vec![vec![]; n];
    for (i, &p) in to_parent.iter().enumerate() {
        adj[p - 1].push(i + 1);
    }

    let mut insurance_map: Vec<Vec<usize>> = vec![vec![]; n];
    for [x, y] in insurances {
        insurance_map[x - 1].push(y);
    }

    // DFS with tracking max insurance depth
    let mut result = 0;
    let dfs = RecursiveClosure::new(|dfs, (v, d): (usize, Option<usize>)| {
        let d = d.max(insurance_map[v].iter().max().copied());
        if d.is_some() {
            result += 1;
        }
        for &u in &adj[v] {
            dfs.call((
                u,
                d.map(|d| if d > 0 { Some(d - 1) } else { None }).flatten(),
            ));
        }
    });
    dfs.call((0, None));
    println!("{}", result);
}

/*
python misc/run.py atcoder/abc309/e/main_v2.rs

%%%% begin
7 3
1 2 1 3 3 3
1 1
1 2
4 3
%%%%
4
%%%% end

%%%% begin
10 10
1 1 3 1 2 3 3 5 7
2 1
5 1
4 3
6 3
2 1
7 3
9 2
1 2
6 2
8 1
%%%%
10
%%%% end
*/

//
// utils
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
