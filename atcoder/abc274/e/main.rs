// AC

// https://atcoder.jp/contests/abc274/tasks/abc274_e

use std::{fmt::Debug, io, str::FromStr};

fn main_case() -> io::Result<()> {
    // n ~ 12, m ~ 5
    let (n, m) = read_tokens::<usize>().map(|v| (v[0], v[1]))?;

    // k ~ 17  ((2^k) k^2 = 37_879_808)
    let k = n + m;

    let mut positions: Vec<(isize, isize)> = vec![];
    for _ in 0..n {
        positions.push(read_tokens().map(|v| (v[0], v[1]))?);
    }
    for _ in 0..m {
        positions.push(read_tokens().map(|v| (v[0], v[1]))?);
    }

    let get_velocity = |s: usize| -> f64 {
        let num_acc = (s & ((1 << m) - 1) << n).count_ones();
        (2 as f64).powf(num_acc as f64)
    };

    // dp(S, p) = minimum cost of reaching p while visiting S (including p)
    let mut dp: Vec<Vec<f64>> = vec![vec![std::f64::MAX; k]; 1 << k];
    for p in 0..k {
        dp[1 << p][p] = get_distance((0, 0), positions[p]);
    }
    for s in 0..(1 << k) {
        for p1 in 0..k {
            if s & (1 << p1) == 0 {
                continue;
            }
            for p2 in 0..k {
                if s & (1 << p2) != 0 {
                    continue;
                }
                let s_next = s | (1 << p2);
                let v = get_velocity(s);
                let d = get_distance(positions[p1], positions[p2]);
                dp[s_next][p2] = dp[s_next][p2].min(dp[s][p1] + d / v);
                // debug
                // println!("-- {} -> {} --", to_bits(s, k), to_bits(s_next, k));
                // dbg!(d, v, dp[s][p1], dp[s_next][p2]);
            }
        }
    }

    // come back to origin
    let mut result = std::f64::MAX;
    let s_town = (1 << n) - 1;
    for s in 0..(1 << k) {
        if s & s_town != s_town {
            continue;
        }
        for p in 0..k {
            let v = get_velocity(s);
            let d = get_distance((0, 0), positions[p]);
            result = result.min(dp[s][p] + d / v);
        }
    }
    println!("{}", result);

    Ok(())
}

fn get_distance((x1, y1): (isize, isize), (x2, y2): (isize, isize)) -> f64 {
    let dx = (x1 - x2).abs() as f64;
    let dy = (y1 - y2).abs() as f64;
    return (dx * dx + dy * dy).sqrt();
}

#[allow(dead_code)]
fn to_bits(x: usize, n: usize) -> String {
    let mut s = String::new();
    for i in 0..n {
        s.push_str(&((x >> i) & 1).to_string());
    }
    s
}

fn main() -> io::Result<()> {
    main_case()
}

/*
python misc/run.py atcoder/abc274/e/main.rs

%%%% begin
2 1
1 1
0 1
1 0
%%%%
2.5000000000
%%%% end

%%%% begin
2 1
1 1
0 1
100 0
%%%%
3.4142135624
%%%% end

%%%% begin
1 2
4 4
1 0
0 1
%%%%
4.3713203436
%%%% end
*/

//
// utils
//

#[allow(dead_code)]
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
