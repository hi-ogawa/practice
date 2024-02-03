// AC

// https://atcoder.jp/contests/abc328/tasks/abc328_e

fn main() {
    // n ~ 8
    // m ~ (n*(n - 1)/2) ~ 28
    // k ~ 10^15
    let [n, m, k]: [usize; 3] = read_array();
    let edges: Vec<[usize; 3]> = (0..m).map(|_| read_array()).collect();

    // brute-force spanning tree by combination(m, n - 1)
    // complexity = comb(m, n - 1) * n * n = 75_778_560

    let mut result = k;
    generate_combinations(m, n - 1, &mut |s| {
        // DFS to check if tree
        let mut adj: Vec<Vec<usize>> = vec![vec![]; n];
        let mut score = 0;
        for i in bit_iterator(s) {
            let [u, v, w] = edges[i];
            adj[u - 1].push(v - 1);
            adj[v - 1].push(u - 1);
            score += w;
        }

        let mut visited: Vec<bool> = vec![false; n];
        let dfs = RecursiveClosure::new(|dfs, x: usize| {
            visited[x] = true;
            for &y in &adj[x] {
                if !visited[y] {
                    dfs.call(y);
                }
            }
        });
        dfs.call(0);
        if visited.iter().all(|&v| v) {
            result = result.min(score % k);
        }
    });

    println!("{}", result);
}

fn generate_combinations(n: usize, k: usize, callback: &mut dyn FnMut(usize)) {
    fn rec(n: usize, k: usize, acc: usize, callback: &mut dyn FnMut(usize)) {
        if n < k {
            return;
        }
        if k == 0 {
            callback(acc);
            return;
        }
        rec(n - 1, k, acc, callback);
        rec(n - 1, k - 1, acc + (1 << (n - 1)), callback);
    }
    rec(n, k, 0, callback);
}

/*
python misc/run.py atcoder/abc328/e/main_v2.rs

%%%% begin
5 6 328
1 2 99
1 3 102
2 3 86
2 4 94
2 5 95
3 4 81
%%%%
33
%%%% end

%%%% begin
6 5 998244353
1 2 337361568
1 6 450343304
2 3 61477244
2 5 745383438
4 5 727360840
%%%%
325437688
%%%% end

%%%% begin
8 28 936294041850197
1 2 473294720906780
1 3 743030800139244
1 4 709363019414774
1 5 383643612490312
1 6 557102781022861
1 7 623179288538138
1 8 739618599410809
2 3 857687812294404
2 4 893923168139714
2 5 581822471860662
2 6 740549363586558
2 7 307226438833222
2 8 447399029952998
3 4 636318083622768
3 5 44548707643622
3 6 307262781240755
3 7 12070267388230
3 8 700247263184082
4 5 560567890325333
4 6 704726113717147
4 7 588263818615687
4 8 549007536393172
5 6 779230871080408
5 7 825982583786498
5 8 713928998174272
6 7 751331074538826
6 8 449873635430228
7 8 11298381761479
%%%%
11360716373
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
// bit iterator
//

fn bit_iterator(mut s: usize) -> impl Iterator<Item = usize> {
    std::iter::from_fn(move || {
        if s == 0 {
            None
        } else {
            let next = s.trailing_zeros();
            s = s & (s - 1);
            Some(next as usize)
        }
    })
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
