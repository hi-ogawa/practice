// WIP

use std::{collections::BTreeMap, fmt::Debug, io, str::FromStr};

fn main() -> io::Result<()> {
    let tokens: Vec<String> = read_tokens()?;
    let s = &tokens[0];
    let mut counts: BTreeMap<char, usize> = BTreeMap::new();
    for c in s.chars() {
        *counts.entry(c).or_insert(0) += 1;
    }
    let mut done = false;
    for (&c, &count) in counts.iter() {
        if count == 1 {
            done = true;
            println!("{}", c);
            break;
        }
    }
    if !done {
        println!("{}", -1);
    }
    Ok(())
}

/*
python misc/run.py atcoder/abc260/a/main.rs

%%%% begin
pop
%%%%
o
%%%% end

%%%% begin
abc
%%%%
a
%%%% end

%%%% begin
xxx
%%%%
-1
%%%% end
*/

//
// io
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
