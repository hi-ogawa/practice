// WIP

// https://atcoder.jp/contests/abc308/tasks/abc308_f

fn main() {
    // ~ 10^5
    let [n, m]: [usize; 2] = read_array();
    // ~ 10^9
    let mut ps: Vec<usize> = read_vec();
    let mut lds: Vec<[usize; 2]> = vec![[0; 2]; m];
    for i in 0..2 {
        for (j, &x) in read_vec::<usize>().iter().enumerate() {
            lds[j][i] = x;
        }
    }

    // problem is equivalent to
    //   maximum applied coupon discount

    // optimal coupon applications can be ordered aginst order items
    // where each coupon is applied again minimal possible price's item
    ps.sort();
    lds.sort_by_key(|ld| ld[0]);

    // TODO: need to minimize "last used item" index as well, so dp won't work?

    // dp(i, 0) = (maximum coupon disount sum, last used item) without coupon 'i'
    // dp(i, 1) = ...                                          with    coupon 'i'
    let mut dp: Vec<[[usize; 2]; 2]> = vec![[[0; 2]; 2]; n + 1];

    for i in 0..n {
        let [l, d] = lds[i];
        // find next apply-able item P for L
        // dp[i];
        dp[i + 1][0] = dp[i][0];
        dp[i][1];
    }
}

/*
python misc/run.py atcoder/abc308/f/main.rs

%%%% begin
3 3
4 3 1
4 4 2
2 3 1
%%%%
4
%%%% end

%%%% begin
10 5
9 7 1 5 2 2 5 5 7 6
7 2 7 8 2
3 2 4 1 2
%%%%
37
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
