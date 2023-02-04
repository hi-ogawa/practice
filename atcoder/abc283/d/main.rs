// AC

// https://atcoder.jp/contests/abc283/tasks/abc283_d

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // |s| ~ 10^5
    let s = read_tokens::<String>()?[0].clone();

    let mut stack: Vec<char> = vec![];
    let mut char_box: Vec<bool> = vec![false; 1 << 8];

    let mut solve = || -> bool {
        for c in s.chars() {
            match c {
                '(' => {
                    stack.push('(');
                }
                ')' => loop {
                    let c = stack.pop().unwrap();
                    match c {
                        '(' => break,
                        ')' => unreachable!(),
                        _ => {
                            assert!(char_box[c as usize]);
                            char_box[c as usize] = false;
                        }
                    }
                },
                _ => {
                    if char_box[c as usize] {
                        return false;
                    }
                    char_box[c as usize] = true;
                    stack.push(c);
                }
            }
        }
        true
    };

    let result = solve();
    println!("{}", if result { "Yes" } else { "No" });
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc283/d/main.rs

%%%% begin
((a)ba)
%%%%
Yes
%%%% end

%%%% begin
(a(ba))
%%%%
No
%%%% end

%%%% begin
(((())))
%%%%
Yes
%%%% end

%%%% begin
abca
%%%%
No
%%%% end

%%%% begin
a(b)a
%%%%
No
%%%% end
*/

//
// utils
//

#[allow(dead_code)]
fn read_tokens<F: FromStr>() -> io::Result<Vec<F>>
where
    <F as FromStr>::Err: Debug,
{
    let mut line = String::new();
    io::stdin().read_line(&mut line)?;
    let mut result: Vec<F> = Vec::new();
    for token in line.trim().split(' ') {
        let value: F = token
            .parse()
            .map_err(|e| io::Error::new(io::ErrorKind::Other, format!("{:?}", e)))?;
        result.push(value);
    }
    Ok(result)
}
