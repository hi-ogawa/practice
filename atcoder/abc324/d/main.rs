// AC

// https://atcoder.jp/contests/abc324/tasks/abc324_d

fn main() {
    // n ~ 13
    let n: usize = read_vec()[0];
    let s: usize = read_vec()[0];

    let to_digits = |mut x: usize| -> [usize; 13] {
        let mut ls = [0; 13];
        for i in 0..n {
            ls[i] = x % 10;
            x /= 10;
        }
        ls.sort();
        ls
    };

    let answer = to_digits(s);
    let square_max = 10usize.pow(n as u32);

    // brute force squares (10^n/2)
    let result = (0..10_000_000)
        .take_while(|x| x * x < square_max)
        .filter(|x| to_digits(x * x) == answer)
        .count();
    println!("{}", result);
}

/*
python misc/run.py atcoder/abc324/d/main.rs

%%%% begin
4
4320
%%%%
2
%%%% end

%%%% begin
3
010
%%%%
2
%%%% end

%%%% begin
13
8694027811503
%%%%
840
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
