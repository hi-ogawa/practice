// AC

// https://atcoder.jp/contests/abc286/tasks/abc286_c

fn main() {
    // n ~ 10^4
    let (n, a, b) = {
        let v: Vec<usize> = read_tokens();
        (v[0], v[1], v[2])
    };
    let s: Vec<char> = read_tokens::<String>()[0].chars().collect();
    let at = |i: usize, rotate: usize| -> char { s[(i + rotate) % n] };

    // solve for each rotation
    let solve = |r: usize| -> usize {
        let mut cost = r * a;
        for i in 0..(n / 2) {
            if at(i, r) != at(n - 1 - i, r) {
                cost += b;
            }
        }
        cost
    };

    let result = (0..n).map(|rotate| solve(rotate)).min().unwrap();
    println!("{}", result);
}

/*
python misc/run.py atcoder/abc286/c/main.rs

%%%% begin
5 1 2
rrefa
%%%%
3
%%%% end

%%%% begin
8 1000000000 1000000000
bcdfcgaa
%%%%
4000000000
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
