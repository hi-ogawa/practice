// WA

// https://atcoder.jp/contests/abc319/tasks/abc319_c

// I thought it's just brute-force but it's stilling missing something...?

fn main() {
    let board: Vec<Vec<usize>> = (0..3).map(|_| read_vec()).collect();

    // collect 16 lines (8 lines x reversals)
    let mut lines: Vec<Vec<(usize, usize)>> = vec![];
    lines.extend((0..3).map(|i| (0..3).map(|j| (i, j)).collect()));
    lines.extend((0..3).map(|i| (0..3).map(|j| (j, i)).collect()));
    lines.push((0..3).map(|i| (i, i)).collect());
    lines.push((0..3).map(|i| (i, 2 - i)).collect());
    lines.extend(
        lines
            .clone()
            .into_iter()
            .map(|line| line.into_iter().rev().collect()),
    );

    // collect only bad lines
    let bad_lines: Vec<Vec<usize>> = lines
        .into_iter()
        .filter(|l| board[l[0].0][l[0].1] == board[l[1].0][l[1].1])
        .map(|l| l.into_iter().map(|(i, j)| 3 * i + j).collect()) // encode as 0..9
        .collect();
    // dbg!(&bad_lines);

    let check_bad = |perm: &Vec<usize>, line: &Vec<usize>| -> bool {
        let mut indices = [0, 0, 0];
        for (i, x) in perm.iter().enumerate() {
            for (j, y) in line.iter().enumerate() {
                if x == y {
                    indices[j] = i;
                }
            }
        }
        indices[0] < indices[2] && indices[1] < indices[2]
    };

    // brute-force permutations(9)
    // 9! x 9 x 16
    let mut bad_count = 0;
    iterate_permutations(9, &mut |perm| {
        if bad_lines.iter().any(|line| check_bad(perm, line)) {
            bad_count += 1;
        }
    });
    // dbg!(bad_count);

    let total = factorial(9);
    let result = ((total - bad_count) as f64) / (total as f64);
    println!("{}", result);
}

fn factorial(n: usize) -> usize {
    if n <= 1 {
        1
    } else {
        n * factorial(n - 1)
    }
}

/*
python misc/run.py atcoder/abc319/c/main.rs

%%%% begin
3 1 9
2 5 6
2 7 1
%%%%
0.666666666666666666666666666667
%%%% end

%%%% begin
7 7 6
8 6 8
7 7 6
%%%%
0.004982363315696649029982363316
%%%% end

%%%% begin
3 6 7
1 9 7
5 7 5
%%%%
0.4
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

//
// permutations
//

fn iterate_permutations(n: usize, callback: &mut dyn FnMut(&Vec<usize>)) {
    fn inner(s: usize, v: &mut Vec<usize>, callback: &mut dyn FnMut(&Vec<usize>)) {
        if s == 0 {
            callback(v);
            return;
        }
        for i in bit_iterator(s) {
            v.push(i);
            inner(s ^ (1 << i), v, callback);
            v.pop();
        }
    }
    inner((1 << n) - 1, &mut vec![], callback);
}

fn bit_iterator(mut s: usize) -> impl Iterator<Item = usize> {
    std::iter::from_fn(move || {
        if s == 0 {
            None
        } else {
            let next = s.trailing_zeros();
            s = s & (s - 1);
            Some(next as usize)
        }
    })
}
