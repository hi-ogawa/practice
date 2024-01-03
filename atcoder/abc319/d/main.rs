// AC

// https://atcoder.jp/contests/abc319/tasks/abc319_d

fn main() {
    // n, m ~ 10^5
    let [n, m]: [usize; 2] = read_array();
    // l ~ 10^9
    let ls: Vec<usize> = read_vec();

    let check_width = |w: usize| -> bool {
        let mut i: usize = 0;
        let mut j: usize = 0;
        for &x in &ls {
            if x > w {
                return false;
            }
            if j + x > w {
                i += 1;
                j = x + 1;
                continue;
            }
            j += x + 1;
        }
        i < m
    };

    // binary search
    let w_max = ls.iter().sum::<usize>() + n;
    let result = binary_search(0, w_max, &|w| check_width(w));
    println!("{}", result);
}

fn binary_search(mut x0: usize, mut x1: usize, f: &dyn Fn(usize) -> bool) -> usize {
    assert!(f(x1));
    while x0 + 1 < x1 {
        let x = (x0 + x1 + 1) / 2;
        if f(x) {
            x1 = x;
        } else {
            x0 = x;
        }
    }
    x1
}

/*
python misc/run.py atcoder/abc319/d/main.rs

%%%% begin
13 3
9 5 2 7 1 8 8 2 1 5 2 3 6
%%%%
26
%%%% end

%%%% begin
10 1
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000
%%%%
10000000009
%%%% end

%%%% begin
30 8
8 55 26 97 48 37 47 35 55 5 17 62 2 60 23 99 73 34 75 7 46 82 84 29 41 32 31 52 32 60
%%%%
189
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
