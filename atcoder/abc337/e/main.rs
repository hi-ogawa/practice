// AC

// https://atcoder.jp/contests/abc337/tasks/abc337_e

fn main() {
    // n ~ 100
    let n: usize = read_vec()[0];

    // construct optimal mapping as digits
    // (TODO: prove)
    let k = (n as f64).log2().ceil() as usize;
    println!("{}", k);

    for b in 0..k {
        let drinks: Vec<usize> = (0..n).filter(|i| i & (1 << b) != 0).collect();
        print!("{}", drinks.len());
        for b in drinks {
            print!(" {}", b + 1);
        }
        println!("");
    }

    let bits: Vec<char> = read_vec::<String>()[0].chars().collect();
    let result: usize = bits
        .iter()
        .enumerate()
        .map(|(i, &b)| if b == '1' { 1 << i } else { 0 })
        .sum();
    println!("{}", result + 1);
}

/*
python misc/run.py atcoder/abc337/e/main.rs

%%%% begin
6
110
%%%%
3
3 2 4 6
2 3 4
2 5 6
4
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
