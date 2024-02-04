// AC

// https://atcoder.jp/contests/abc331/tasks/abc331_e

use std::collections::BTreeSet;

fn main() {
    // ~ 10^5
    let [_n, _m, l]: [usize; 3] = read_array();
    let ls1: Vec<usize> = read_vec();
    let ls2: Vec<usize> = read_vec();

    let bad_pairs: BTreeSet<[usize; 2]> = (0..l).map(|_| read_array()).collect();

    // sort descending "b"
    let mut ls2: Vec<(usize, usize)> = ls2.into_iter().enumerate().collect();
    ls2.sort_by_key(|&(_i, v)| v);
    ls2.reverse();

    // for each "a", pick largest "b"
    let mut result = 0;
    for (i, a) in ls1.iter().enumerate() {
        for (j, b) in &ls2 {
            if !bad_pairs.contains(&[i + 1, j + 1]) {
                result = result.max(a + b);
                break;
            }
        }
    }

    println!("{}", result);
}

/*
python misc/run.py atcoder/abc331/e/main.rs

%%%% begin
2 3 3
2 1
10 30 20
1 2
2 1
2 3
%%%%
31
%%%% end

%%%% begin
2 1 0
1000000000 1
1000000000
%%%%
2000000000
%%%% end

%%%% begin
10 10 10
47718 21994 74148 76721 98917 73766 29598 59035 69293 29127
7017 46004 16086 62644 74928 57404 32168 45794 19493 71590
1 3
2 6
4 5
5 4
5 5
5 6
5 7
5 8
5 10
7 3
%%%%
149076
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
