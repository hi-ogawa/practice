// WIP

// https://atcoder.jp/contests/abc320/tasks/abc320_c

fn main() {
    let m: usize = read_vec()[0];
    let n = 3;
    let ls: Vec<Vec<usize>> = (0..n)
        .map(|_| {
            read_vec::<String>()[0]
                .chars()
                .map(|c| c.to_digit(10).unwrap() as usize)
                .collect()
        })
        .collect();

    // if solvable, it takes at most n * m steps
    let k = n * m;
    let max_d = 10;

    // solve for digit "d" and given "order" independently
    let solve = |d: usize, order: &Vec<usize>| -> Option<usize> {
        let mut j = 0;
        for i in 0..k {
            if ls[order[j]][i % m] == d {
                j += 1;
                if j == order.len() {
                    return Some(i);
                }
            }
        }
        None
    };

    // brute-force
    let mut order: Vec<usize> = (0..n).collect();
    let mut results: Vec<Option<usize>> = vec![];
    loop {
        for d in 0..max_d {
            results.push(solve(d, &order));
        }
        if !next_permutation(&mut order) {
            break;
        }
    }

    let result = results.iter().flatten().min();
    if let Some(x) = result {
        println!("{}", x);
    } else {
        println!("-1");
    }
}

/*
python misc/run.py atcoder/abc320/c/main.rs

%%%% begin
10
1937458062
8124690357
2385760149
%%%%
6
%%%% end

%%%% begin
20
01234567890123456789
01234567890123456789
01234567890123456789
%%%%
20
%%%% end

%%%% begin
5
11111
22222
33333
%%%%
-1
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
