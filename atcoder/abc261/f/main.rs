// AC

use std::{fmt::Debug, io, str::FromStr};

//
// fenwick tree
//

#[derive(Debug, Clone)]
struct FenwickTree {
    n: usize,
    data: Vec<isize>,
}

impl FenwickTree {
    fn new(n: usize) -> Self {
        Self {
            n,
            data: vec![0; n],
        }
    }

    fn change(&mut self, mut i: usize, delta: isize) {
        while i < self.n {
            self.data[i] += delta;
            i = i | (i + 1); // change least significant zero to one
        }
    }

    fn range_sum(&self, l: usize, r: usize) -> isize {
        self.range_sum_impl(r) - self.range_sum_impl(l)
    }

    fn range_sum_impl(&self, mut i: usize) -> isize {
        let mut result = 0;
        while i > 0 {
            i -= 1;
            result += self.data[i];
            i = i & (i + 1); // change trailing ones to zeros
        }
        result
    }
}

//
// main
//

fn main_case() -> io::Result<()> {
    let n: usize = read_tokens()?[0]; // [2, 3 x 10^5]
    let c_vec: Vec<usize> = read_tokens()?; // [1, N]
    let x_vec: Vec<usize> = read_tokens()?; // [1, N]

    // all indices order by x
    let mut all_indices: Vec<usize> = (0..n).collect();
    all_indices.sort_by_key(|&i| x_vec[i]);

    // do same for each color
    let mut color_indices: Vec<Vec<usize>> = vec![vec![]; n + 1];
    for (i, &c) in c_vec.iter().enumerate() {
        color_indices[c].push(i);
    }
    for indices in color_indices.iter_mut() {
        indices.sort_by_key(|&i| x_vec[i]);
    }

    // range count
    let mut tree = FenwickTree::new(n);
    for i in 0..n {
        tree.change(i, 1);
    }

    // remove from smallest `x` and count on the left
    let mut count_left1: Vec<isize> = vec![0; n];
    for &i in &all_indices {
        count_left1[i] = tree.range_sum(0, i);
        tree.change(i, -1);
    }

    // do same for each color
    let mut count_left2: Vec<isize> = vec![0; n];
    for indices in color_indices.iter() {
        for &i in indices {
            tree.change(i, 1);
        }
        for &i in indices {
            count_left2[i] = tree.range_sum(0, i);
            tree.change(i, -1);
        }
    }

    // #{different color on the left} = #{ any color ...} - #{ same color ...}
    let mut result: isize = 0;
    for i in 0..n {
        result += count_left1[i] - count_left2[i];
    }
    println!("{}", result);

    Ok(())
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc261/f/main.rs

%%%% begin
5
1 5 2 2 1
3 2 1 2 1
%%%%
6
%%%% end

%%%% begin
3
1 1 1
3 2 1
%%%%
0
%%%% end

%%%% begin
3
3 1 2
1 1 2
%%%%
0
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
