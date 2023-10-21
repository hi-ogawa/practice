// AC

// https://atcoder.jp/contests/abc311/tasks/abc311_e

// simplified DP part ofr main.rs

fn main() {
    // h, w ~ 10^3
    // n ~ 10^5
    let [h, w, n]: [usize; 3] = read_array();
    let mut blocks: Vec<Vec<bool>> = vec![vec![false; w]; h];
    for _ in 0..n {
        let [a, b]: [usize; 2] = read_array();
        blocks[a - 1][b - 1] = true;
    }

    // pre-compute closest block for right/down direction for each cell
    let mut closest: Vec<Vec<[usize; 2]>> = vec![vec![[0, 0]; w]; h];
    for i in 0..h {
        let mut block = w;
        for j in (0..w).rev() {
            if blocks[i][j] {
                block = j;
            }
            closest[i][j][1] = block - j;
        }
    }
    for j in 0..w {
        let mut block = h;
        for i in (0..h).rev() {
            if blocks[i][j] {
                block = i;
            }
            closest[i][j][0] = block - i;
        }
    }

    // DP for each diagonal ray (from bottom/right to top/left)
    let mut dp: Vec<Vec<usize>> = vec![vec![0; w + 1]; h + 1];
    for i in (0..h).rev() {
        for j in (0..w).rev() {
            dp[i][j] = (dp[i + 1][j + 1] + 1)
                .min(closest[i][j][0])
                .min(closest[i][j][1]);
        }
    }
    let result: usize = dp.iter().map(|row| row.iter().sum::<usize>()).sum();
    println!("{}", result);
}

/*
python misc/run.py atcoder/abc311/e/main_v2.rs

%%%% begin
2 3 1
2 3
%%%%
6
%%%% end

%%%% begin
3 2 6
1 1
1 2
2 1
2 2
3 1
3 2
%%%%
0
%%%% end

%%%% begin
1 1 0
%%%%
1
%%%% end

%%%% begin
3000 3000 0
%%%%
9004500500
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
