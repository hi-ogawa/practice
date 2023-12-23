// WIP

// https://atcoder.jp/contests/abc314/tasks/abc314_d

fn main() {
    // n, q ~ 10^5
    let n: usize = read_vec()[0];
    let s: Vec<char> = read_vec::<String>()[0].chars().collect();
    let q: usize = read_vec()[0];

    // `usize` to track step
    let mut state: Vec<(char, usize)> = s.iter().map(|&c| (c, 0)).collect();

    // true -> all capital at `usize` step
    // false -> all lower at ...
    let mut all_op: Option<(bool, usize)> = None;

    for j in 0..q {
        let [t, x, c]: [String; 3] = read_array();
        match t.as_str() {
            "1" => {
                let x: usize = x.parse().unwrap();
                state[x - 1] = (c.chars().next().unwrap(), j);
            }
            "2" => {
                all_op = Some((false, j));
            }
            "3" => {
                all_op = Some((true, j));
            }
            _ => unreachable!(),
        }
    }

    // dbg!(&state);
    // dbg!(&all_op);
    if let Some((is_upper, j)) = all_op {
        for i in 0..n {
            if state[i].1 <= j {
                state[i].0 = if is_upper {
                    state[i].0.to_ascii_uppercase()
                } else {
                    state[i].0.to_ascii_lowercase()
                };
            }
        }
    }

    let result = state.iter().map(|&(c, _)| c).collect::<String>();
    println!("{}", result);
}

/*
python misc/run.py atcoder/abc314/d/main.rs

%%%% begin
7
AtCoder
5
1 4 i
3 0 a
1 5 b
2 0 a
1 4 Y
%%%%
atcYber
%%%% end

%%%% begin
35
TheQuickBrownFoxJumpsOverTheLazyDog
10
2 0 a
1 19 G
1 13 m
1 2 E
1 21 F
2 0 a
1 27 b
3 0 a
3 0 a
1 15 i
%%%%
TEEQUICKBROWMFiXJUGPFOVERTBELAZYDOG
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
