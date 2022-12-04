// WA

// https://atcoder.jp/contests/abc278/tasks/abc278_f

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // n ~ 16
    let n: usize = read_tokens()?[0];

    let mut ls: Vec<(char, char)> = vec![];
    for _ in 0..n {
        // |s| ~ 10
        let s = read_tokens::<String>()?[0].clone();
        ls.push((s.chars().next().unwrap(), s.chars().last().unwrap()));
    }

    let mut adj: Vec<Vec<usize>> = vec![vec![]; n];
    for i in 0..n {
        for j in 0..n {
            if i == j {
                continue;
            }
            if ls[i].1 == ls[j].0 {
                adj[i].push(j);
            }
        }
    }
    // dbg!(&adj);

    // for x ∈ S, define
    //   dp(S, x) = 1  \iff  first wins when starting from x for the game of subset S

    let mut dp: Vec<Vec<bool>> = vec![vec![false; n]; 1 << n];

    for s in 0..(1 << n) {
        for x in 0..n {
            if s & (1 << x) != 0 {
                let t = s & !(1 << x);
                dp[s][x] = adj[x].iter().any(|&y| (t & (1 << y) != 0) && !dp[t][y]);
            }
        }
    }
    // dbg!(&dp);

    let result = (0..n).any(|x| dp[(1 << n) - 1][x]);
    println!("{}", if result { "First" } else { "Second" });
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc278/f/main.rs

%%%% begin
3
a
b
c
%%%%
Second
%%%% end

%%%% begin
6
enum
float
if
modint
takahashi
template
%%%%
First
%%%% end

%%%% begin
10
catch
chokudai
class
continue
copy
exec
havoc
intrinsic
static
yucatec
%%%%
Second
%%%% end

%%%% begin
16
mnofcmzsdx
lgeowlxuqm
ouimgdjxlo
jhwttcycwl
jbcuioqbsj
mdjfikdwix
jhvdpuxfil
peekycgxco
sbvxszools
xuuqebcrzp
jsciwvdqzl
obblxzjhco
ptobhnpfpo
muizaqtpgx
jtgjnbtzcl
sivwidaszs
%%%%
First
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
