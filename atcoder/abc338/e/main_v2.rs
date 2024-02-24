// AC

// https://atcoder.jp/contests/abc338/tasks/abc338_e

fn main() {
    // ~ 10^5
    let n: usize = read_vec()[0];
    let mut ls: Vec<[usize; 2]> = (0..n).map(|_| read_array()).collect();

    // check edge in-out makes stack such as
    // ++++++++++ +++++++ +++++
    //  ++++++     +++     +++
    //    +++               +

    // position, id, in/out
    let mut events: Vec<(usize, usize, bool)> = vec![];
    for i in 0..n {
        ls[i].sort();
        events.push((ls[i][0], i, true));
        events.push((ls[i][1], i, false));
    }
    events.sort();

    let mut stack: Vec<usize> = vec![];
    for &(_, i, is_in) in &events {
        if is_in {
            stack.push(i);
        } else {
            let j = stack.pop();
            if j != Some(i) {
                println!("Yes");
                return;
            }
        }
    }
    println!("No");
}

/*
python misc/run.py atcoder/abc338/e/main_v2.rs

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
