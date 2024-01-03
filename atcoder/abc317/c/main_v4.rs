// AC

// https://atcoder.jp/contests/abc317/tasks/abc317_c

// iterate permutations based on
// https://en.cppreference.com/w/cpp/algorithm/next_permutation

use std::cell::RefCell;

fn main() {
    // n ~ 10
    let [n, m]: [usize; 2] = read_array();
    let mut adj: Vec<Vec<Option<usize>>> = vec![vec![None; n]; n];
    for _ in 0..m {
        let [a, b, c]: [usize; 3] = read_array();
        adj[a - 1][b - 1] = Some(c);
        adj[b - 1][a - 1] = Some(c);
    }

    let mut result = 0;
    for perm in permutation_iterator_in_place(n) {
        let perm = perm.borrow(); // a little inconvenient...
        let score: usize = (0..(n - 1))
            .map(|i| adj[perm[i]][perm[i + 1]])
            .map_while(|c| c)
            .sum();
        result = result.max(score);
    }

    // do-while style iteration without iterator abstraction
    // let mut result = 0;
    // let mut perm: Vec<usize> = (0..n).collect();
    // loop {
    //     let score: usize = (0..(n - 1))
    //         .map(|i| adj[perm[i]][perm[i + 1]])
    //         .map_while(|c| c)
    //         .sum();
    //     result = result.max(score);
    //     if !next_permutation(&mut perm) {
    //         break;
    //     }
    // }

    println!("{}", result);
}

fn permutation_iterator_in_place(n: usize) -> impl Iterator<Item = RefCell<Vec<usize>>> {
    let mut first = true;
    let perm = RefCell::new((0..n).collect::<Vec<usize>>());
    std::iter::from_fn(move || {
        if first || next_permutation(&mut perm.borrow_mut()) {
            first = false;
            Some(perm.clone())
        } else {
            None
        }
    })
}

// https://stackoverflow.com/a/68607168
#[allow(dead_code)]
fn permutation_iterator_copy(n: usize) -> impl Iterator<Item = Vec<usize>> {
    let mut first = true;
    let mut perm: Vec<usize> = (0..n).collect();
    std::iter::from_fn(move || {
        if first || next_permutation(&mut perm) {
            first = false;
            Some(perm.clone())
        } else {
            None
        }
    })
}

fn next_permutation(v: &mut Vec<usize>) -> bool {
    //
    // 1. find suffix s.t.
    //
    // ... x  <  y1 >= .. >= yk >= .. >= yn
    //
    // where k = max { i | y_i > x }
    //
    // 2. by swapping (x, yk),
    //
    // ... yk <= y1 >= .. >= x  >= .. >= yn
    //
    // 3. by reversing (y1, ..., yn)
    //
    // ... yk <= yn <= .. <= x  <= .. <= r1
    //

    // 1.0. find descending suffix
    let n = v.len();
    let i = (1..n).rev().find(|&i| v[i - 1] < v[i]);
    if i.is_none() {
        return false;
    }

    // 1.1. find y_k > x
    let i = i.unwrap();
    let j = i + v[i..n].partition_point(|&y| y > v[i - 1]) - 1;

    // 2.
    v.swap(i - 1, j);

    // 3.
    for d in 0..((n - i) / 2) {
        v.swap(i + d, n - 1 - d);
    }
    true
}

/*
python misc/run.py atcoder/abc317/c/main_v4.rs

%%%% begin
4 4
1 2 1
2 3 10
1 3 100
1 4 1000
%%%%
1110
%%%% end

%%%% begin
10 1
5 9 1
%%%%
1
%%%% end

%%%% begin
10 13
1 2 1
1 10 1
2 3 1
3 4 4
4 7 2
4 8 1
5 8 1
5 9 3
6 8 1
6 9 5
7 8 1
7 9 4
9 10 3
%%%%
20
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
