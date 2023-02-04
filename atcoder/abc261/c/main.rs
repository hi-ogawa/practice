// AC

use std::{collections::BTreeMap, fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let n: usize = read_tokens()?[0];
    let mut counts: BTreeMap<String, usize> = BTreeMap::new();
    for _ in 0..n {
        let s = &read_tokens::<String>()?[0];
        let count = counts.entry(s.clone()).or_insert(0);
        if *count > 0 {
            println!("{}({})", s, count);
        } else {
            println!("{}", s);
        }
        *count += 1;
    }
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc261/c/main.rs

%%%% begin
5
newfile
newfile
newfolder
newfile
newfolder
%%%%
newfile
newfile(1)
newfolder
newfile(2)
newfolder(1)
%%%% end

%%%% begin
11
a
a
a
a
a
a
a
a
a
a
a
%%%%
a
a(1)
a(2)
a(3)
a(4)
a(5)
a(6)
a(7)
a(8)
a(9)
a(10)
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
    for token in line.trim().split(' ') {
        let value: F = token
            .parse()
            .map_err(|e| io::Error::new(io::ErrorKind::Other, format!("{:?}", e)))?;
        result.push(value);
    }
    Ok(result)
}
