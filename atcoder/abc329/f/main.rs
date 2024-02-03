// AC

// https://atcoder.jp/contests/abc329/tasks/abc329_f

use std::collections::BTreeSet;

fn main() {
    // n, nq ~ 10^5
    let [n, nq]: [usize; 2] = read_array();
    let mut ls: Vec<BTreeSet<usize>> = vec![BTreeSet::new(); n];
    for (i, &x) in read_vec::<usize>().iter().enumerate() {
        ls[i].insert(x);
    }

    for _ in 0..nq {
        let [mut a, mut b]: [usize; 2] = read_array();
        a -= 1;
        b -= 1;
        // merge from small to large
        if ls[a].len() > ls[b].len() {
            ls.swap(a, b);
        }
        // TODO: clone necessary for borrow checker?
        for x in ls[a].clone() {
            ls[b].insert(x);
        }
        ls[a].clear();
        println!("{}", ls[b].len());
    }
}

/*
python misc/run.py atcoder/abc329/f/main.rs

%%%% begin
6 5
1 1 1 2 2 3
1 2
6 4
5 1
3 6
4 6
%%%%
1
2
1
1
3
%%%% end

%%%% begin
5 3
2 4 2 4 2
3 1
2 5
3 2
%%%%
1
2
0
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
