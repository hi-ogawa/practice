// WA

// https://atcoder.jp/contests/abc283/tasks/abc283_d

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // |s| ~ 10^5
    let s = read_tokens::<String>()?[0].clone();

    // stack for each alphabets
    let mut stacks: Vec<Vec<char>> = vec![vec![]; 1 << 8];
    let mut char_box: Vec<bool> = vec![false; 1 << 8];

    let mut solve = || -> bool {
        for c in s.chars() {
            match c {
                '(' => {
                    // rust 1.42.0
                    for i in ('a' as usize)..=('z' as usize) {
                        stacks[i].push('(');
                    }
                }
                ')' => {
                    for i in ('a' as usize)..=('z' as usize) {
                        // pop each stack and update char_box
                        let mut count = 1;
                        let stack = &mut stacks[i];
                        while let Some(c) = stack.pop() {
                            match c {
                                '(' => {
                                    if count == 0 {
                                        stack.push('(');
                                        break;
                                    }
                                    count -= 1;
                                }
                                ')' => {
                                    count += 1;
                                }
                                _ => {
                                    assert!(char_box[c as usize]);
                                    char_box[c as usize] = false;
                                }
                            }
                        }
                        assert!(count == 0);
                    }
                }
                _ => {
                    if char_box[c as usize] {
                        return false;
                    }
                    char_box[c as usize] = true;
                    stacks[c as usize].push(c);
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
Yes
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
    for token in line.trim().split(" ") {
        let value: F = token
            .parse()
            .map_err(|e| io::Error::new(io::ErrorKind::Other, format!("{:?}", e)))?;
        result.push(value);
    }
    Ok(result)
}
