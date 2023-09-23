// AC

// https://atcoder.jp/contests/abc290/tasks/abc290_d

fn main_case() {
    // ~ 10^9
    let (n, d, k) = {
        let v: Vec<usize> = read_tokens();
        (v[0], v[1], v[2])
    };

    // gcd(n, d)
    let g = gcd(n, d);
    let l = n * d / g; // lcm(n, d)
    let o = l / d; // order of cyclic sub group <d> ⊆ Zn

    // to zero-based in dex
    let k = k - 1;

    // each cycle offsets by one => (k / o)
    // number of remaining steps => (k % o)
    let result = ((k / o) + (k % o) * d) % n;
    println!("{}", result);
}

fn gcd(x: usize, y: usize) -> usize {
    // workaround CE https://atcoder.jp/contests/abc290/submissions/39590113
    let mut t = (x, y);
    if t.0 < t.1 {
        t = (t.1, t.0);
    };
    while t.1 > 0 {
        t = (t.1, t.0 % t.1);
    }
    t.0
}

fn main() {
    let t: usize = read_tokens()[0];
    for _ in 0..t {
        main_case();
    }
}

/*
python misc/run.py atcoder/abc290/d/main.rs

%%%% begin
9
4 2 1
4 2 2
4 2 3
4 2 4
5 8 1
5 8 2
5 8 3
5 8 4
5 8 5
%%%%
0
2
1
3
0
3
1
4
2
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
