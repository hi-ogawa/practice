// AC

// https://atcoder.jp/contests/abc301/tasks/abc301_d

fn main() {
    // |s| ~ 60
    let s: Vec<char> = read_tokens::<String>()[0].chars().rev().collect();
    let n: usize = read_tokens()[0];

    // check if solvable
    let mut result = from_bits(&mut s.iter().map(|&c| c == '1'));
    if result > n {
        println!("-1");
        return;
    }

    // solve from significant bits
    for (i, &c) in s.iter().enumerate().rev() {
        if c == '?' {
            let next = result | (1 << i);
            if next <= n {
                result = next;
            }
        }
    }
    println!("{}", result);
}

fn from_bits(bits: &mut dyn Iterator<Item = bool>) -> usize {
    let mut res = 0;
    for (i, b) in bits.enumerate() {
        if b {
            res = res | (1 << i);
        }
    }
    res
}

/*
python misc/run.py atcoder/abc301/d/main.rs

%%%% begin
?0?
2
%%%%
1
%%%% end

%%%% begin
101
4
%%%%
-1
%%%% end

%%%% begin
?0?
1000000000000000000
%%%%
5
%%%% end
*/

//
// utils
//

#[allow(dead_code)]
fn read_tokens<T: std::str::FromStr>() -> Vec<T>
where
    <T as std::str::FromStr>::Err: std::fmt::Debug,
{
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).unwrap();
    line.split_whitespace()
        .map(|s| s.parse().unwrap())
        .collect()
}
