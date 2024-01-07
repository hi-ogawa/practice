// AC

// https://atcoder.jp/contests/abc322/tasks/abc322_e

fn main() {
    // n ~ 100
    // k, p ~ 5
    let [n, k, p]: [usize; 3] = read_array();

    // c ~ 10^9
    let mut costs: Vec<usize> = vec![];
    let mut gains: Vec<Vec<usize>> = vec![];
    for _ in 0..n {
        let v: Vec<usize> = read_vec();
        costs.push(v[0]);
        gains.push(v[1..].iter().copied().collect());
    }

    // encode/decode state into index
    type State = [usize; 5];

    let enc = |state: State| -> usize {
        let mut j = 0;
        for x in state {
            j = j * (p + 1) + x;
        }
        j
    };
    let dec = |mut j: usize| -> State {
        let mut state = [0; 5];
        for x in state.iter_mut().rev() {
            *x = j % (p + 1);
            j = j / (p + 1);
        }
        state
    };

    let m = enc([p; 5]);

    // dp(i, s) = min cost to reach state "s" using "C1..Ci"
    let mut dp: Vec<Vec<Option<usize>>> = vec![vec![None; m + 1]; n + 1];
    dp[0][enc([0; 5])] = Some(0);

    // n x (p + 1)^k
    for i in 0..n {
        for j in 0..=m {
            dp[i + 1][j] = option_min(dp[i + 1][j], dp[i][j]);

            let mut s = dec(j);
            for x in 0..k {
                s[x] = (s[x] + gains[i][x]).min(p);
            }
            let j2 = enc(s);
            dp[i + 1][j2] = option_min(dp[i + 1][j2], option_add(dp[i][j], costs[i]));
        }
    }

    let mut max_state: State = [0; 5];
    for i in 0..k {
        max_state[i] = p;
    }
    if let Some(result) = dp[n][enc(max_state)] {
        println!("{}", result);
    } else {
        println!("{}", -1);
    }
}

fn option_add(x: Option<usize>, y: usize) -> Option<usize> {
    x.map(|x| x + y)
}

fn option_min(x: Option<usize>, y: Option<usize>) -> Option<usize> {
    [x, y].iter().flatten().copied().min()
}

/*
python misc/run.py atcoder/abc322/e/main.rs

%%%% begin
4 3 5
5 3 0 2
3 1 2 3
3 2 4 0
1 0 1 4
%%%%
9
%%%% end

%%%% begin
7 3 5
85 1 0 1
37 1 1 0
38 2 0 0
45 0 2 2
67 1 1 0
12 2 2 0
94 2 2 1
%%%%
-1
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
