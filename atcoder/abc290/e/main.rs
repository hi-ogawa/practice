// AC

// https://atcoder.jp/contests/abc290/tasks/abc290_e

use std::collections::HashMap;

fn main() {
    // ~ 10^5
    let n: usize = read_tokens()[0];
    let ls: Vec<usize> = read_tokens();

    //
    // compute cost if all elements were distinct
    //
    let mut base_cost = 0;
    for l in 2..=n {
        base_cost += (l / 2) * (n + 1 - l);
    }

    //
    // subtract by the factor by coinciding pairs
    //

    // collect indices with same values
    let mut groups: HashMap<usize, Vec<usize>> = HashMap::new();
    for (i, &a) in ls.iter().enumerate() {
        groups.entry(a).or_default().push(i);
    }

    #[rustfmt::skip]
    fn compute_subtraction(indices: &Vec<usize>, n: usize) -> usize {
        // ∑_{i < j} min(l_i, r_j)
        let ls: Vec<usize> = indices.iter().map(|i| i + 1).collect(); // incr
        let rs: Vec<usize> = indices.iter().map(|i| n - i).collect(); // decr
        let k = indices.len();
        let mut acc = 0;
        for i in 0..k {
            // acc += l_i * |{ r | r_i >  r > l_i }|
            // acc += r_i * |{ l | r_i <= l < l_i }|
            let l_i = ls[i];
            let r_i = rs[i];
            if r_i > l_i {
                acc += l_i * (
                    binary_search_max(0, k, |i| rs[i] >  l_i).map_or(-1, |x| x as isize) -
                    binary_search_max(0, k, |i| rs[i] >= r_i).map_or(-1, |x| x as isize)
                ) as usize;
            }
            if r_i < l_i {
                acc += r_i * (
                    binary_search_max(0, k, |i| ls[i] < l_i).map_or(-1, |x| x as isize) -
                    binary_search_max(0, k, |i| ls[i] < r_i).map_or(-1, |x| x as isize)
                ) as usize;
            }
        }
        acc
    }

    let mut subtraction = 0;
    for indices in groups.values() {
        subtraction += compute_subtraction(indices, n);
    }

    let result = base_cost - subtraction;
    println!("{}", result);
}

//
// binary search
//

// max { x \in [x0, x1) | f(x) }
fn binary_search_max<F: Fn(usize) -> bool>(mut x0: usize, mut x1: usize, f: F) -> Option<usize> {
    if !f(x0) {
        return None;
    }
    while x0 + 1 < x1 {
        let x = (x0 + x1) / 2;
        if f(x) {
            x0 = x;
        } else {
            x1 = x;
        }
    }
    Some(x0)
}

/*
python misc/run.py atcoder/abc290/e/main.rs

%%%% begin
5
5 2 1 2 2
%%%%
9
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
