// AC

// https://atcoder.jp/contests/abc299/tasks/abc299_d

fn main() {
    // [2, 2 x 10^5]
    let n: usize = read_tokens()[0];

    let f = |x: usize| -> bool {
        println!("? {}", x);
        let y: usize = read_tokens()[0];
        y == 0
    };

    // find max { x \in [x0, x1) | f(x) }
    let binary_search_max = |mut x0: usize, mut x1: usize| -> usize {
        // assert!(f(x0));
        // assert!(!f(x1));
        while x0 + 1 < x1 {
            let x = (x0 + x1) / 2;
            if f(x) {
                x0 = x;
            } else {
                x1 = x;
            }
        }
        x0
    };

    let result = binary_search_max(1, n);
    println!("! {}", result);
}

/*
python misc/run.py atcoder/abc299/d/main.rs

%%%% begin
7
0
0
1
%%%%
? 4
? 5
? 6
! 5
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
