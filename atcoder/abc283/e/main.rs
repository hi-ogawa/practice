// AC

// https://atcoder.jp/contests/abc283/tasks/abc283_e

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // ~ 10^3
    let (h, w) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;
    let mut board: Vec<Vec<usize>> = vec![];
    for _ in 0..h {
        board.push(read_tokens()?);
    }

    //
    // precompute constraints for each three rows
    //

    let mut constraints: Vec<Vec<bool>> = vec![vec![false; 0b1000]; h];

    // return true if the middle row of three rows doesn't have isolated cells
    let check_three = |i: usize, flip: usize| -> bool {
        (0..w).all(|j| {
            #[rustfmt::skip]
            return
                (0 < j     && board[i][j] == board[i][j - 1]) ||
                (j < w - 1 && board[i][j] == board[i][j + 1]) ||
                (0 < i     && board[i][j] ^ ((flip >> 1) & 1) == board[i - 1][j] ^ (flip & 1)) ||
                (i < h - 1 && board[i][j] ^ ((flip >> 1) & 1) == board[i + 1][j] ^ ((flip >> 2) & 1));
        })
    };

    for i in 0..h {
        for flip in 0..(1 << 3) {
            constraints[i][flip] = check_three(i, flip);
        }
    }

    //
    // dp
    //

    const NO_VALUE: usize = std::usize::MAX;
    let mut dp: Vec<Vec<usize>> = vec![vec![NO_VALUE; 0b1000]; h];

    for flip in 0..(1 << 3) {
        if constraints[0][flip] {
            dp[0][flip] = (flip >> 1) & 1;
        }
    }

    for i in 1..h {
        for flip1 in 0..0b1000 {
            for flip2 in 0..0b1000 {
                if (flip1 >> 1) & 0b11 == flip2 & 0b11
                    && constraints[i - 1][flip1]
                    && constraints[i][flip2]
                    && dp[i - 1][flip1] != NO_VALUE
                {
                    dp[i][flip2] = dp[i][flip2].min(dp[i - 1][flip1] + ((flip2 >> 1) & 1));
                }
            }
        }
    }

    // debug dp
    // dbg!(&constraints);
    // dbg!(&dp);

    let &result = dp[h - 1].iter().min().unwrap();
    if result == NO_VALUE {
        println!("-1");
    } else {
        println!("{}", result);
    }
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc283/e/main.rs

%%%% begin
3 3
1 1 0
1 0 1
1 0 0
%%%%
1
%%%% end

%%%% begin
4 4
1 0 0 0
0 1 1 1
0 0 1 0
1 1 0 1
%%%%
2
%%%% end

%%%% begin
2 3
0 1 0
0 1 1
%%%%
-1
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
