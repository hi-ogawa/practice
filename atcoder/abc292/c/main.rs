// AC

// https://atcoder.jp/contests/abc292/tasks/abc292_c

fn main() {
    // n ~ 10^5
    let n: usize = read_tokens()[0];

    // ls[k] = |{ (a, b) | a x b = k }|
    let mut ls: Vec<usize> = vec![0; n + 1];

    // complexity ~ ∑_{x <= n}(n / x) ~ n ∑(1 / x) ~ n logn (cf. harmonic partial sum)
    for a in 1..=n {
        for k in (a..=n).step_by(a) {
            ls[k] += 1;
        }
    }

    let mut result = 0;
    for i in 0..=n {
        result += ls[i] * ls[n - i];
    }
    println!("{}", result);
}

/*
python misc/run.py atcoder/abc292/c/main.rs

%%%% begin
4
%%%%
8
%%%% end

%%%% begin
292
%%%%
10886
%%%% end

%%%% begin
19876
%%%%
2219958
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
