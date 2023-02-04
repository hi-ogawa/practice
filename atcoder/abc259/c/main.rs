// AC

// https://atcoder.jp/contests/abc259/tasks/abc259_c

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // length [2, 2 x 10^5]
    let s1 = read_tokens::<String>()?[0].clone();
    let s2 = read_tokens::<String>()?[0].clone();

    // split into components
    fn split(s: &String) -> Vec<(char, usize)> {
        let s: Vec<char> = s.chars().collect();
        if s.len() == 0 {
            return vec![];
        }
        let mut result = vec![(s[0], 1)];
        for i in 1..s.len() {
            if s[i] != s[i - 1] {
                result.push((s[i], 1));
            } else {
                result.last_mut().unwrap().1 += 1;
            }
        }
        result
    }

    let components1 = split(&s1);
    let components2 = split(&s2);

    if components1.len() == components2.len() {
        if (0..components1.len()).all(|i| {
            let (c1, d1) = components1[i];
            let (c2, d2) = components2[i];
            c1 == c2 && (d1 == d2 || (2 <= d1 && d1 <= d2))
        }) {
            println!("Yes");
            return Ok(());
        }
    }

    println!("No");
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc259/c/main.rs

%%%% begin
abbaac
abbbbaaac
%%%%
Yes
%%%% end

%%%% begin
xyzz
xyyzz
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
