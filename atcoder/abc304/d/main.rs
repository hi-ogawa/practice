// AC

// https://atcoder.jp/contests/abc304/tasks/abc304_d

use std::collections::HashMap;

fn main() {
    // w, h ~ 10^9
    let v: Vec<usize> = read_tokens();
    let (_w, _h) = (v[0], v[1]);

    // n ~ 10^5
    let n: usize = read_tokens()[0];
    let mut points: Vec<Vec<usize>> = vec![];
    for _ in 0..n {
        points.push(read_tokens());
    }

    let a: usize = read_tokens()[0];
    let mut xs: Vec<usize> = read_tokens();
    let b: usize = read_tokens()[0];
    let mut ys: Vec<usize> = read_tokens();

    // boundary for simplicity
    xs.insert(0, 0);
    ys.insert(0, 0);

    let mut counts: HashMap<(usize, usize), usize> = HashMap::new();

    for v in &points {
        let i = binary_search_max(v[0], &xs);
        let j = binary_search_max(v[1], &ys);
        *counts.entry((i, j)).or_default() += 1;
    }

    let max = counts.values().max().unwrap();
    let min = if counts.len() < (a + 1) * (b + 1) {
        0
    } else {
        *counts.values().min().unwrap()
    };
    println!("{} {}", min, max);
}

// max { i | xs[i] < x }
fn binary_search_max(x: usize, xs: &Vec<usize>) -> usize {
    let mut i0 = 0;
    let mut i1 = xs.len();
    while i0 + 1 < i1 {
        let i = (i0 + i1) / 2;
        if xs[i] < x {
            i0 = i;
        } else {
            i1 = i
        }
    }
    i0
}

/*
python misc/run.py atcoder/abc304/d/main.rs

%%%% begin
7 6
5
6 1
3 1
4 2
1 5
6 2
2
2 5
2
3 4
%%%%
0 2
%%%% end

%%%% begin
4 4
4
1 1
3 1
3 3
1 3
1
2
1
2
%%%%
1 1
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
