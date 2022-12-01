// AC

// https://atcoder.jp/contests/abc277/tasks/abc277_c

use std::{
    collections::{HashMap, HashSet},
    fmt::Debug,
    io,
    str::FromStr,
};

fn main_case() -> io::Result<()> {
    // n ~ 10^5
    let n: usize = read_tokens()?[0];

    let mut adj: HashMap<usize, Vec<usize>> = HashMap::new();
    for _ in 0..n {
        // a, b ~ 10^9
        let (a, b) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;
        adj.entry(a).or_default().push(b);
        adj.entry(b).or_default().push(a);
    }

    // bfs
    let mut queue: Vec<usize> = vec![];
    let mut visited: HashSet<usize> = HashSet::new();
    queue.push(1);
    visited.insert(1);
    while let Some(v) = queue.pop() {
        if let Some(ls) = adj.get(&v) {
            for &u in ls {
                if visited.contains(&u) {
                    continue;
                }
                visited.insert(u);
                queue.push(u);
            }
        }
    }

    let result = visited.iter().max().unwrap();
    println!("{}", result);
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc277/c/main.rs

%%%% begin
4
1 4
4 3
4 10
8 3
%%%%
10
%%%% end

%%%% begin
6
1 3
1 5
1 12
3 5
3 12
5 12
%%%%
12
%%%% end

%%%% begin
3
500000000 600000000
600000000 700000000
700000000 800000000
%%%%
1
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
