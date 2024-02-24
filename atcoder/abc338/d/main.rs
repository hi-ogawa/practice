// WA

// https://atcoder.jp/contests/abc338/tasks/abc338_d

fn main() {
    // ~ 10^5
    let [n, m]: [usize; 2] = read_array();
    let ls: Vec<usize> = read_vec();

    // initially when 1..n
    let mut to_left: Vec<Vec<usize>> = vec![vec![]; n];
    let mut to_right: Vec<Vec<usize>> = vec![vec![]; n];
    let mut result = 0;
    for i in 0..(m - 1) {
        let mut x = ls[i] - 1;
        let mut y = ls[i + 1] - 1;
        if x > y {
            [x, y] = [y, x]
        }
        result += y - x;
        to_right[x].push(y);
        to_left[y].push(x);
    }

    // incrementally update when moving a cut
    let mut result_acc = result;
    for i in 0..(n - 1) {
        // collect pairs to flip
        let mut pairs: Vec<(usize, usize)> = vec![];
        for &j in &to_right[i] {
            pairs.push((i, j));
        }
        for &j in &to_left[i + 1] {
            pairs.push((j, i + 1));
        }
        pairs.sort();
        pairs.dedup();

        // flip
        let i0 = i;
        let j0 = i + 1;
        to_right[i0].clear();
        to_left[j0].clear();
        for &(i, j) in &pairs {
            if i < j {
                result += i + n - j;
                result -= j - i;
            } else {
                result += i - j;
                result -= j + n - i;
            }
            to_right[j].push(i);
            to_left[i].push(j);
        }
        result_acc = result_acc.min(result);
    }
    println!("{}", result_acc);
}

/*
python misc/run.py atcoder/abc338/d/main.rs

%%%% begin
3 3
1 3 2
%%%%
2
%%%% end

%%%% begin
4 5
2 4 2 4 2
%%%%
8
%%%% end

%%%% begin
163054 10
62874 19143 77750 111403 29327 56303 6659 18896 64175 26369
%%%%
390009
%%%% end
*/

//
// utils
//

#[allow(dead_code)]
fn read_vec<T: std::str::FromStr>() -> Vec<T> {
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).unwrap();
    line.split_whitespace()
        .map(|s| s.parse().ok().unwrap())
        .collect()
}

#[allow(dead_code)]
fn read_array<T: std::str::FromStr, const LEN: usize>() -> [T; LEN] {
    #[allow(unused_imports)]
    use std::convert::TryInto;
    read_vec::<T>().try_into().ok().unwrap()
}
