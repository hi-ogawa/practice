// WA

// https://atcoder.jp/contests/abc338/tasks/abc338_e

// This configuration is also possible...
//   5 -- 0
//  4      1
//   \    /
//   3    2

fn main() {
    // ~ 10^5
    let n: usize = read_vec()[0];
    let mut ls: Vec<[usize; 2]> = (0..n).map(|_| read_array()).collect();

    // TODO: only possible configuraiton?
    //   5 -- 0
    //  4 ---- 1
    //   3 -- 2

    // normalize into such configuration
    let k = ls.iter().find_map(|&[x, y]| {
        if x.abs_diff(y) == 1 {
            Some(x.max(y))
        } else {
            None
        }
    });
    if k.is_none() {
        println!("Yes");
        return;
    }
    let k = k.unwrap();
    for i in 0..n {
        ls[i][0] = (ls[i][0] + 2 * n - k) % (2 * n);
        ls[i][1] = (ls[i][1] + 2 * n - k) % (2 * n);
        ls[i].sort();
    }
    ls.sort();

    // verify configuration
    let ok = (0..n).all(|i| ls[i] == [i, 2 * n - i - 1]);
    println!("{}", if ok { "No" } else { "Yes" });
}

/*
python misc/run.py atcoder/abc338/e/main.rs

%%%% begin
3
1 3
4 2
5 6
%%%%
Yes
%%%% end

%%%% begin
3
6 1
4 3
2 5
%%%%
No
%%%% end

%%%% begin
4
2 4
3 7
8 6
5 1
%%%%
Yes
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
