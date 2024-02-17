// AC

// https://atcoder.jp/contests/abc336/tasks/abc336_d

fn main() {
    // n ~ 10^5
    let n: usize = read_vec()[0];
    let ls: Vec<usize> = read_vec();

    // construct "boosted" sequence and take cummulative-min
    let mut ls1: Vec<usize> = ls.clone();
    for i in 0..n {
        ls1[i] += i;
    }
    for i in (0..(n - 1)).rev() {
        ls1[i] = ls1[i].min(ls1[i + 1]);
    }

    // do opposite "boost"
    let mut ls2: Vec<usize> = ls.clone();
    for i in 0..n {
        ls2[i] += n - 1 - i;
    }
    for i in 0..(n - 1) {
        ls2[i + 1] = ls2[i + 1].min(ls2[i]);
    }

    // find pyramid
    let mut result = 1;
    for i in 0..n {
        let v = [ls1[i] - i, ls2[i] - (n - 1 - i), i + 1, n - i]
            .iter()
            .min()
            .copied()
            .unwrap();
        result = result.max(v);
    }
    println!("{}", result);
}

/*
python misc/run.py atcoder/abc336/d/main.rs

%%%% begin
5
2 2 3 1 1
%%%%
2
%%%% end

%%%% begin
5
1 2 3 4 5
%%%%
3
%%%% end

%%%% begin
1
1000000000
%%%%
1
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
