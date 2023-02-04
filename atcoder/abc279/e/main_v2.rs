// AC

// https://atcoder.jp/contests/abc279/tasks/abc279_e

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // n, m ~ 10^5
    let (n, m) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;

    // A \in [0, n - 2]
    let ls: Vec<usize> = read_tokens()?;
    let ls: Vec<usize> = ls.iter().map(|&x| x - 1).collect();

    // precompute all permutation
    let mut perm_suffix = Permutaton::new(n);
    for i in 0..m {
        perm_suffix.swap(ls[i], ls[i] + 1);
    }

    // incrementally compute
    let mut perm = Permutaton::new(n);
    for i in 0..m {
        // revert prefix swap
        perm_suffix.swap_pre(ls[i], ls[i] + 1);

        // merge prefix/suffix mapping
        let result = perm_suffix.map[perm.map[0]] + 1;
        println!("{}", result);

        // apply prefix swap
        perm.swap(ls[i], ls[i] + 1);
    }

    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

//
// permutation
//

struct Permutaton {
    map: Vec<usize>,
    inv_map: Vec<usize>, // i.e. final order of (0, .., n - 1) when the mapping is applied
}

impl Permutaton {
    fn new(n: usize) -> Self {
        Self {
            inv_map: (0..n).collect(),
            map: (0..n).collect(),
        }
    }

    fn swap(&mut self, i: usize, j: usize) {
        self.map.swap(self.inv_map[i], self.inv_map[j]);
        self.inv_map.swap(i, j);
    }

    fn swap_pre(&mut self, i: usize, j: usize) {
        self.inv_map.swap(self.map[i], self.map[j]);
        self.map.swap(i, j);
    }
}

/*
python misc/run.py atcoder/abc279/e/main_v2.rs

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
