// AC

// https://atcoder.jp/contests/abc304/tasks/abc304_e

use std::collections::HashSet;

fn main() {
    // ~ 10^5
    let v: Vec<usize> = read_tokens();
    let (n, m) = (v[0], v[1]);

    // find connected components
    let mut dsu = Dsu::new(n);
    for _ in 0..m {
        let v: Vec<usize> = read_tokens();
        dsu.merge(v[0] - 1, v[1] - 1);
    }
    let dsu_find: Vec<usize> = (0..n).map(|i| dsu.find(i)).collect();

    // collect required component pairs
    let mut pairs: HashSet<(usize, usize)> = HashSet::new();
    let k: usize = read_tokens()[0];
    for _ in 0..k {
        let v: Vec<usize> = read_tokens();
        let x = dsu_find[v[0] - 1];
        let y = dsu_find[v[1] - 1];
        assert!(x != y);
        pairs.insert((x, y));
        pairs.insert((y, x));
    }

    // check each query breaks requirement
    let q: usize = read_tokens()[0];
    for _ in 0..q {
        let v: Vec<usize> = read_tokens();
        let x = dsu_find[v[0] - 1];
        let y = dsu_find[v[1] - 1];
        let result = if pairs.contains(&(x, y)) { "No" } else { "Yes" };
        println!("{}", result);
    }
}

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

/*
python misc/run.py atcoder/abc304/e/main.rs

%%%% begin
6 6
1 2
2 3
2 3
3 1
5 4
5 5
3
1 5
2 6
4 3
4
2 5
2 6
5 6
5 4
%%%%
No
No
Yes
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
