// AC

// https://atcoder.jp/contests/abc278/tasks/abc278_d

use std::{collections::HashMap, fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // n ~ 10^5
    let _n: usize = read_tokens()?[0];
    // a \in [0, 10^9]
    let ls: Vec<usize> = read_tokens()?;
    // q ~ 10^5
    let q: usize = read_tokens()?[0];

    let mut ls_map: HashMap<usize, usize> = HashMap::new();
    for (i, &a) in ls.iter().enumerate() {
        ls_map.insert(i, a);
    }
    let mut default: usize = 0;

    for _ in 0..q {
        let query = read_tokens::<String>()?;
        match query[0].as_str() {
            "1" => {
                default = query[1].parse().unwrap();
                ls_map = HashMap::new();
            }
            "2" => {
                let i = query[1].parse::<usize>().unwrap() - 1;
                let x = query[2].parse::<usize>().unwrap();
                *ls_map.entry(i).or_insert(default) += x;
            }
            "3" => {
                let i = query[1].parse::<usize>().unwrap() - 1;
                let result = ls_map.get(&i).unwrap_or(&default);
                println!("{}", result);
            }
            _ => unreachable!(),
        }
    }

    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc278/d/main.rs

%%%% begin
5
3 1 4 1 5
6
3 2
2 3 4
3 3
1 1
2 3 4
3 3
%%%%
1
8
5
%%%% end

%%%% begin
1
1000000000
8
2 1 1000000000
2 1 1000000000
2 1 1000000000
2 1 1000000000
2 1 1000000000
2 1 1000000000
2 1 1000000000
3 1
%%%%
8000000000
%%%% end

%%%% begin
10
1 8 4 15 7 5 7 5 8 0
20
2 7 0
3 7
3 8
1 7
3 3
2 4 4
2 4 9
2 10 5
1 10
2 4 2
1 10
2 3 1
2 8 11
2 3 14
2 1 9
3 8
3 8
3 1
2 6 5
3 7
%%%%
7
5
7
21
21
19
10
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
