// AFTER EDITORIAL

// https://atcoder.jp/contests/abc330/tasks/abc330_e

// can just use set...

use std::collections::BTreeSet;

fn main() {
    // PROP. MEX exists [0, n] by pigeon-hole principle

    // n ~ 10^5
    let [n, nq]: [usize; 2] = read_array();
    let mut ls: Vec<usize> = read_vec();

    // - track existance only up to "n"
    // - use prefix sum and binrary search to find MEX
    let mut counts: Vec<usize> = vec![0; n + 1];
    let mut set: BTreeSet<usize> = (0..=n).collect();
    for &x in &ls {
        if x <= n {
            counts[x] += 1;
            set.remove(&x);
        }
    }

    for _ in 0..nq {
        let [mut i, x]: [usize; 2] = read_array();
        i -= 1;
        if ls[i] != x {
            if ls[i] <= n {
                counts[ls[i]] -= 1;
                if counts[ls[i]] == 0 {
                    set.insert(ls[i]);
                }
            }
            if x <= n {
                if counts[x] == 0 {
                    set.remove(&x);
                }
                counts[x] += 1;
            }
            ls[i] = x;
        }
        let result = *set.first().unwrap();
        println!("{}", result);
    }
}

/*
python misc/run.py atcoder/abc330/e/main_v2.rs

%%%% begin
8 5
2 0 2 2 1 1 2 5
4 3
4 4
6 3
8 1000000000
2 1
%%%%
4
3
6
5
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
