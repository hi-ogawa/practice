// AFTER EDITORIAL, AC

use std::{
    collections::{BTreeMap, BTreeSet},
    fmt::Debug,
    io,
    str::FromStr,
};

fn main_case() -> io::Result<()> {
    let (n, m) = read_tokens::<usize>().map(|v| (v[0], v[1]))?; // [1, 2 x 10^5]
    let mut rev_map: Vec<Vec<usize>> = vec![vec![]; m + 1];

    for i in 0..n {
        let v: Vec<usize> = read_tokens()?;
        rev_map[v[0]].push(i);
        rev_map[v[1]].push(i);
    }

    // collect valid lengths as intervals
    let mut pre_result: Vec<(usize, usize)> = vec![];

    {
        // sliding window
        let mut l = 1usize;
        let mut r = 0usize;
        let mut counts: BTreeMap<usize, usize> = BTreeMap::new();

        while l <= m {
            // find minimal segment by incrementing `r`
            while counts.len() != n && r < m {
                r += 1;
                for &i in rev_map[r].iter() {
                    *counts.entry(i).or_default() += 1
                }
            }
            if counts.len() == n {
                pre_result.push((r + 1 - l, m + 1 - l));
            } else {
                break;
            }

            // increment `l`
            for &i in rev_map[l].iter() {
                let count = counts.get_mut(&i).unwrap();
                *count -= 1;
                if *count == 0 {
                    counts.remove(&i);
                }
            }
            l += 1;
        }
    }

    // aggregate by sweeping intervals
    let mut result: Vec<usize> = vec![0; m + 1];

    {
        let mut rev_pre_result: Vec<Vec<(bool, usize)>> = vec![vec![]; m + 2];

        for (i, &(l, r)) in pre_result.iter().enumerate() {
            rev_pre_result[l].push((true, i));
            rev_pre_result[r + 1].push((false, i));
        }

        let mut acc: BTreeSet<usize> = BTreeSet::new();

        for l in 1..=m {
            for &(t, i) in rev_pre_result[l].iter() {
                if t {
                    acc.insert(i);
                } else {
                    acc.remove(&i);
                }
            }
            result[l] = acc.len();
        }
    }

    println!(
        "{}",
        result[1..=m]
            .iter()
            .map(|x| x.to_string())
            .collect::<Vec<_>>()
            .join(" ")
    );
    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc260/e/main.rs

%%%% begin
3 5
1 3
1 4
2 5
%%%%
0 1 3 2 1
%%%% end

%%%% begin
1 2
1 2
%%%%
2 1
%%%% end

%%%% begin
5 9
1 5
1 7
5 6
5 8
2 6
%%%%
0 0 1 2 4 4 3 2 1
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
