// AC

// https://atcoder.jp/contests/abc357/tasks/abc357_e

fn main() {
    // n ~ 10^5
    let n: usize = read_vec()[0];
    let mut adj: Vec<usize> = read_vec();
    for i in 0..n {
        adj[i] -= 1;
    }

    // DP on DFS
    let mut scores: Vec<Option<usize>> = vec![None; n];
    let mut depths: Vec<Option<usize>> = vec![None; n];

    let dfs = RecursiveClosure::new(|dfs, (x, depth): (usize, usize)| -> (usize, usize) {
        if let Some(score) = scores[x] {
            return (depth, score);
        }
        if let Some(d) = depths[x] {
            return (d, depth - d);
        }
        depths[x] = Some(depth);
        let (loop_depth, score) = dfs.call((adj[x], depth + 1));
        let new_score = if depth >= loop_depth {
            score
        } else {
            score + 1
        };
        scores[x] = Some(new_score);
        (loop_depth, new_score)
    });

    for x in 0..n {
        dfs.call((x, 0));
    }
    // dbg!(&scores);

    let result: usize = scores.into_iter().flatten().sum();
    println!("{}", result);
}

/*
python misc/run.py atcoder/abc357/e/main.rs

%%%% begin
4
2 1 1 4
%%%%
8
%%%% end

%%%% begin
5
2 4 3 1 2
%%%%
14
%%%% end

%%%% begin
10
6 10 4 1 5 9 8 6 5 1
%%%%
41
%%%% end
*/

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
