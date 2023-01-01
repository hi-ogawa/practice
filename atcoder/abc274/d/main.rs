// AC

// https://atcoder.jp/contests/abc274/tasks/abc274_d

use std::{collections::HashSet, fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // n ~ 10^3
    // x, y ~ 10^4
    let (_n, x, y) = read_tokens::<isize>().map(|v| (v[0], v[1], v[2]))?;

    // a \in [1, 10]
    let ls: Vec<isize> = read_tokens()?;

    // solve each x and y independently
    fn solve(src: isize, dst: isize, ls: Vec<isize>) -> bool {
        let mut dp: HashSet<isize> = HashSet::new();
        dp.insert(src);
        // ~ 10^3
        for &a in &ls {
            let mut dp_next: HashSet<isize> = HashSet::new();
            // ~ 10^4
            for i in dp {
                dp_next.insert(i + a);
                dp_next.insert(i - a);
            }
            dp = dp_next;
        }
        dp.contains(&dst)
    }

    let ok_x = solve(
        ls[0],
        x,
        ls.clone().into_iter().skip(2).step_by(2).collect(),
    );
    let ok_y = solve(0, y, ls.clone().into_iter().skip(1).step_by(2).collect());
    let result = ok_x && ok_y;
    println!("{}", if result { "Yes" } else { "No" });

    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc274/d/main.rs

%%%% begin
3 -1 1
2 1 3
%%%%
Yes
%%%% end

%%%% begin
5 2 0
2 2 2 2 2
%%%%
Yes
%%%% end

%%%% begin
4 5 5
1 2 3 4
%%%%
No
%%%% end

%%%% begin
3 2 7
2 7 4
%%%%
No
%%%% end

%%%% begin
10 8 -7
6 10 4 1 5 9 8 6 5 1
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
