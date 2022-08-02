// WA

use std::{fmt::Debug, io, str::FromStr};

// TODO: prove necessity

fn main_case() -> io::Result<()> {
    let n: usize = read_tokens()?[0];
    let s: Vec<_> = read_tokens::<String>()?[0].chars().collect();

    let mut ok = true;

    for i in 0..n {
        let j = n - 1 - i;
        if i > j {
            break;
        }
        match (s[i], s[j]) {
            ('A', 'A') | ('B', 'B') => {
                // TODO: in this case, we could do some arbitrary changes to the inner string to

                // A ? . . . A
                // ~~~
                // A B . . . A

                // B . . . ? B
                //         ~~~
                // B . . . A B

                continue;
            }
            ('A', 'B') => {
                ok = false;
                break;
            }
            ('B', 'A') => {
                if i + 1 == j {
                    ok = false;
                }
                break;
            }
            _ => unreachable!(),
        }
    }

    println!("{}", if ok { "Yes" } else { "No" });

    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/arc145/a/main.rs

%%%% begin
3
BBA
%%%%
Yes
%%%% end

%%%% begin
4
ABAB
%%%%
No
%%%% end
*/

//
// utils
//

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
