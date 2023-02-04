// AC

// https://atcoder.jp/contests/abc271/tasks/abc271_d

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // n \in [1, 100]
    // s \in [1, 10000]
    let (n, s) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;
    let mut ls: Vec<(usize, usize)> = vec![];
    for _ in 0..n {
        // a, b \in [1, 100]
        ls.push(read_tokens::<usize>().map(|v| (v[0], v[1]))?);
    }

    // dp[i][x] = Some(head/tail)  \iff  `[(a1, b1) ... (ai, bi)]` can make sum `x` where choosing ai/bi
    let mut dp: Vec<Vec<Option<bool>>> = vec![vec![None; s + 1]; n + 1];
    dp[0][0] = Some(true); // dummy "head" for boundary value
    for i in 0..n {
        let (a, b) = ls[i];
        for x in 0..=s {
            if a <= x && dp[i][x - a].is_some() {
                dp[i + 1][x] = Some(true);
            }
            if b <= x && dp[i][x - b].is_some() {
                dp[i + 1][x] = Some(false);
            }
        }
    }

    let yes = dp[n][s].is_some();
    println!("{}", if yes { "Yes" } else { "No" });
    // dbg!(&dp);

    if yes {
        let mut x = s;
        let mut heads: Vec<bool> = vec![false; n];
        for i in (0..n).rev() {
            match dp[i + 1][x] {
                Some(head) => {
                    heads[i] = head;
                    x -= if head { ls[i].0 } else { ls[i].1 };
                }
                _ => unreachable!(),
            }
        }
        for head in heads {
            print!("{}", if head { 'H' } else { 'T' });
        }
        println!("");
    }

    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc271/d/main.rs

%%%% begin
3 11
1 4
2 3
5 7
%%%%
Yes
HTT
%%%% end

%%%% begin
5 25
2 8
9 3
4 11
5 1
12 6
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
