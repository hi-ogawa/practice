// AC

// https://atcoder.jp/contests/abc279/tasks/abc279_e

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // n, m ~ 10^5
    let (n, m) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;

    // A \in [0, n - 2]
    let ls: Vec<usize> = read_tokens()?;
    let ls: Vec<usize> = ls.iter().map(|&x| x - 1).collect();

    // precompute reverse swaps
    let mut rev_perm: Vec<usize> = (0..n).collect();
    let mut rev_perm_inv: Vec<usize> = (0..n).collect();
    for i in 0..m {
        let x = ls[i];
        rev_perm_inv.swap(rev_perm[x], rev_perm[x + 1]);
        rev_perm.swap(x, x + 1);
    }

    // incrementally compute
    let mut perm: Vec<usize> = (0..n).collect();
    let mut perm_inv: Vec<usize> = (0..n).collect();
    for i in 0..m {
        let x = ls[i];
        // revert reverse swaps
        rev_perm_inv.swap(x, x + 1);

        // merge forawrd/reverse mapping
        let result = rev_perm_inv[perm_inv[0]] + 1;
        println!("{}", result);

        // apply forward swap
        perm_inv.swap(perm[x], perm[x + 1]);
        perm.swap(x, x + 1);
    }

    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc279/e/main.rs

%%%% begin
5 4
1 2 3 2
%%%%
1
3
2
4
%%%% end

%%%% begin
3 3
2 2 2
%%%%
1
1
1
%%%% end

%%%% begin
10 10
1 1 1 9 4 4 2 1 3 3
%%%%
2
2
2
3
3
3
1
3
4
4
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
    for token in line.trim().split(' ') {
        let value: F = token
            .parse()
            .map_err(|e| io::Error::new(io::ErrorKind::Other, format!("{:?}", e)))?;
        result.push(value);
    }
    Ok(result)
}
