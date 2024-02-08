// AC

// https://atcoder.jp/contests/abc333/tasks/abc333_e

fn main() {
    // ~ 10^5
    let n: usize = read_vec()[0];
    // x \in [1, n]
    let ls: Vec<[usize; 2]> = (0..n).map(|_| read_array()).collect();

    // solve reverse problem to find optimal
    // TODO: prove correctness

    let mut required: Vec<usize> = vec![0; n + 1];
    let mut history: Vec<isize> = vec![0; n];

    for (i, &[t, x]) in ls.iter().enumerate().rev() {
        match t {
            1 => {
                if required[x] > 0 {
                    required[x] -= 1;
                    history[i] = 1;
                }
            }
            2 => {
                required[x] += 1;
                history[i] = -1;
            }
            _ => unreachable!(),
        }
    }

    if required.iter().all(|&v| v == 0) {
        let mut acc = history.clone();
        for i in 1..n {
            acc[i] += acc[i - 1];
        }
        let result = acc.iter().max().unwrap();
        println!("{}", result);
        for (i, v) in history.iter().filter(|&&v| v >= 0).enumerate() {
            if i > 0 {
                print!(" ");
            }
            print!("{}", v);
        }
        println!();
    } else {
        println!("-1");
    }
}

/*
python misc/run.py atcoder/abc333/e/main.rs

%%%% begin
13
1 2
1 3
1 1
1 3
1 2
2 3
1 3
1 3
2 3
1 3
2 2
2 3
2 1
%%%%
3
1 1 1 0 0 1 0 1
%%%% end

%%%% begin
4
2 3
1 4
2 1
1 2
%%%%
-1
%%%% end

%%%% begin
30
1 25
1 2
1 10
1 18
2 18
1 11
2 11
1 21
1 6
2 2
2 10
1 11
1 24
1 11
1 3
1 2
1 18
2 25
1 8
1 10
1 11
2 18
2 10
1 10
2 2
1 24
1 10
2 10
1 25
2 6
%%%%
4
1 1 1 1 1 0 1 0 0 0 0 1 1 0 1 0 1 0 0 0
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
