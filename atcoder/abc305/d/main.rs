// AC

// https://atcoder.jp/contests/abc305/tasks/abc305_d

fn main() {
    // n ~ 10^5
    let n: usize = read_tokens()[0];
    // a ~ 10^9
    let ls: Vec<usize> = read_tokens();

    // precompute on boundary
    let mut cumsum: Vec<usize> = vec![0; n + 1];
    for i in 1..n {
        cumsum[i + 1] = cumsum[i] + ((i + 1) % 2) * (ls[i] - ls[i - 1]);
    }

    // solve(t) = (total sleep in [0, t])
    let solve = |t: usize| -> usize {
        // binary search to find closest boundary to the left
        let i = binary_search_max(0, n, |i| ls[i] <= t);
        // add extra when odd
        cumsum[i + 1] + (i % 2) * (t - ls[i])
    };

    let q: usize = read_tokens()[0];
    for _ in 0..q {
        let v: Vec<usize> = read_tokens();
        let (l, r) = (v[0], v[1]);
        let result = solve(r) - solve(l);
        println!("{}", result);
    }
}

// max { i | f(i) }
fn binary_search_max<F: Fn(usize) -> bool>(mut x0: usize, mut x1: usize, f: F) -> usize {
    while x0 + 1 < x1 {
        let x = (x0 + x1) / 2;
        if f(x) {
            x0 = x;
        } else {
            x1 = x;
        }
    }
    x0
}

/*
python misc/run.py atcoder/abc305/d/main.rs

%%%% begin
7
0 240 720 1320 1440 1800 2160
3
480 1920
720 1200
0 2160
%%%%
480
0
960
%%%% end

%%%% begin
21
0 20 62 192 284 310 323 324 352 374 409 452 486 512 523 594 677 814 838 946 1000
10
77 721
255 541
478 970
369 466
343 541
42 165
16 618
222 592
730 983
338 747
%%%%
296
150
150
49
89
20
279
183
61
177
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
