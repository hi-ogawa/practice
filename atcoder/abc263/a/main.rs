// WIP

use std::{collections::BTreeMap, fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let ls = read_tokens::<usize>()?;

    let mut map: BTreeMap<usize, usize> = BTreeMap::new();
    for x in ls {
        *map.entry(x).or_insert(0) += 1;
    }
    let mut counts: Vec<_> = map.iter().map(|(_, &v)| v).collect();
    counts.sort();
    if counts == vec![2, 3] {
        println!("Yes");
    } else {
        println!("No");
    }

    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc263/a/main.rs

%%%% begin
1 2 1 2 1
%%%%
Yes
%%%% end

%%%% begin
12 12 11 1 2
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
