// WIP

// https://atcoder.jp/contests/abc312/tasks/abc312_f

fn main() {
    // m <= n ~ 10^5
    let [n, m]: [usize; 2] = read_array();
    let mut ls: [Vec<usize>; 3] = Default::default();
    for _ in 0..n {
        let [x, t]: [usize; 2] = read_array();
        ls[x].push(t);
    }
    for i in 0..3 {
        ls[i].sort();
        ls[i].reverse();
    }

    // dp[k] = max score when using "k" can openers
    let mut dp: Vec<usize> = vec![0; m + 1];

    let mut i = 0;
    let mut w = m;
    for &x in &ls[0] {
        if w == 0 {
            break;
        }
        dp[0] += x;
        i += 1;
        w -= 1;
    }

    for x in &ls[0][0..i] {
        dp[0] += x;
    }

    let mut j = 0;
    let mut z = 0;

    for k in 1..=m {
        dbg!(dp[k - 1]);

        // replace for next can opener
        if j > 0 {
            j -= 1;
            dp[k] = dp[k - 1] - ls[1][j];
        } else {
            assert!(i > 0);
            i -= 1;
            dp[k] = dp[k - 1] - ls[0][i];
        }
        // replace "ls[0][i - 1]" with "ls[1][j]" up to "z" times
        z += ls[2][k - 1];
        while z > 0 && i > 0 && ls[1].len() > j && ls[1][j] > ls[0][i - 1] {
            dp[k] = dp[k] + ls[1][j] - ls[0][i - 1];
            i -= 1;
            j += 1;
            z -= 0;
        }
    }

    dbg!(dp);
}

/*
python misc/run.py atcoder/abc312/f/main.rs

%%%% begin
8 4
0 6
0 6
1 3
1 5
1 15
2 1
2 10
2 100
%%%%
27
%%%% end

%%%% begin
5 5
1 5
1 5
1 5
1 5
1 5
%%%%
0
%%%% end

%%%% begin
12 6
2 2
0 1
0 9
1 3
1 5
1 3
0 4
2 1
1 8
2 1
0 1
0 4
%%%%
30
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
