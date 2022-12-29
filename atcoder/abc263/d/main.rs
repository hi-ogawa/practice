// WA

use std::{cmp::min_by_key, fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    let (n, l, r) = read_tokens::<isize>().map(|v| (v[0] as usize, v[1], v[2]))?;
    let ls = read_tokens::<isize>()?;

    let mut cumsum = vec![0; n + 1];
    for i in 0..n {
        cumsum[i + 1] += cumsum[i] + ls[i];
    }
    let total = cumsum[n];

    let get_sum_l = |i: usize| (i as isize) * l + (total - cumsum[i]);
    let get_sum_r = |i: usize| cumsum[n - i] + (i as isize) * r;
    let get_sum =
        |i: usize, j: usize| (i as isize) * l + (cumsum[n - j] - cumsum[i]) + (j as isize) * r;

    let l_best = (0..=n).fold(0, |acc, i| min_by_key(acc, i, |&k| get_sum_l(k)));
    let r_best = (0..=n).fold(0, |acc, i| min_by_key(acc, i, |&k| get_sum_r(k)));
    dbg!((l_best, r_best));

    let mut candidates = vec![get_sum_l(n), get_sum_r(n)];
    if l_best < r_best {
        candidates.push(get_sum(l_best, r_best));
    }
    let result = candidates.iter().min().unwrap();
    println!("{}", result);

    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc263/d/main.rs

%%%% begin
5 4 3
5 5 0 6 3
%%%%
14
%%%% end

%%%% begin
4 10 10
1 2 3 4
%%%%
10
%%%% end

%%%% begin
10 -5 -3
9 -6 10 -1 2 10 -1 7 -15 5
%%%%
-58
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
