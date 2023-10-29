// AC

// https://atcoder.jp/contests/abc312/tasks/abc312_c

use std::collections::BTreeMap;

fn main() {
    // ~ 10^5
    let [_n, m]: [usize; 2] = read_array();

    // ~ 10^9
    let mut ls1: Vec<usize> = read_vec();
    let mut ls2: Vec<usize> = read_vec();
    ls1.sort();
    ls2.sort();

    let mut map: BTreeMap<usize, Vec<bool>> = BTreeMap::new();
    for &x in &ls1 {
        map.entry(x).or_default().push(true);
    }
    for &x in &ls2 {
        map.entry(x + 1).or_default().push(false);
    }

    let mut a = 0;
    let mut b = m;
    for (&x, vs) in &map {
        for &v in vs {
            if v {
                a += 1;
            } else {
                b -= 1;
            }
        }
        if a >= b {
            println!("{}", x);
            return;
        }
    }
    unreachable!()
}

/*
python misc/run.py atcoder/abc312/c/main.rs

%%%% begin
3 4
110 90 120
100 80 120 10000
%%%%
110
%%%% end

%%%% begin
5 2
100000 100000 100000 100000 100000
100 200
%%%%
201
%%%% end

%%%% begin
3 2
100 100 100
80 120
%%%%
100
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
