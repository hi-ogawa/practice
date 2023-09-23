// AC

// https://atcoder.jp/contests/abc307/tasks/abc307_d

fn main() {
    let _n: usize = read_tokens()[0];
    let input: Vec<char> = read_tokens::<String>()[0].chars().collect();

    let mut output: Vec<char> = vec![];
    let mut lefts: Vec<usize> = vec![];

    for &c in &input {
        match c {
            '(' => {
                lefts.push(output.len());
                output.push(c);
            }
            ')' => {
                if let Some(i) = lefts.pop() {
                    assert!(i < output.len());
                    assert!(output[i] == '(');
                    output.truncate(i);
                } else {
                    output.push(c);
                }
            }
            _ => output.push(c),
        }
    }

    println!("{}", output.into_iter().collect::<String>());
}

/*
python misc/run.py atcoder/abc307/d/main.rs

%%%% begin
8
a(b(d))c
%%%%
ac
%%%% end

%%%% begin
5
a(b)(
%%%%
a(
%%%% end

%%%% begin
2
()
%%%%

%%%% end

%%%% begin
6
)))(((
%%%%
)))(((
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
