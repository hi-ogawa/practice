// AC

// https://atcoder.jp/contests/abc287/tasks/abc287_d

fn main() {
    // 0 < |t| < |s| ~ 10^5
    let s: Vec<char> = read_tokens::<String>()[0].chars().collect();
    let t: Vec<char> = read_tokens::<String>()[0].chars().collect();

    let m = s.len();
    let n = t.len();

    // solve prefix/suffix
    let mut prefix = vec![true; n + 1];
    let mut suffix = vec![true; n + 1];

    fn is_match(x: char, y: char) -> bool {
        x == y
            || match (x, y) {
                ('?', _) | (_, '?') => true,
                _ => false,
            }
    }
    for i in 0..n {
        prefix[i + 1] = prefix[i] && is_match(s[i], t[i]);
        suffix[i + 1] = suffix[i] && is_match(s[m - 1 - i], t[n - 1 - i]);
    }

    // answer
    for i in 0..=n {
        let result = if prefix[i] && suffix[n - i] {
            "Yes"
        } else {
            "No"
        };
        println!("{}", result);
    }
}

/*
python misc/run.py atcoder/abc287/d/main.rs

%%%% begin
a?c
b?
%%%%
Yes
No
No
%%%% end

%%%% begin
atcoder
?????
%%%%
Yes
Yes
Yes
Yes
Yes
Yes
%%%% end

%%%% begin
beginner
contest
%%%%
No
No
No
No
No
No
No
No
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
