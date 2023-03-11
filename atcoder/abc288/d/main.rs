// WIP

// https://atcoder.jp/contests/abc288/tasks/abc288_d

//
// PROP.
//   k-solvable => "greedily" k-solvable (i.e. eliminating from left to right)
//
// proof.
//   - operation is order independent
//   - if solvable, reorder such operations based on left
//   - such re-ordered operations clrealy represents "greedly" solution
//

fn main() {
    // n ~ 10^5
    // k ~ 10
    let (n, k) = {
        let v: Vec<usize> = read_tokens();
        (v[0], v[1])
    };
    let ls: Vec<isize> = read_tokens();

    let q: usize = read_tokens()[0];
    for _ in 0..q {
        let (l, r) = {
            let v: Vec<usize> = read_tokens();
            (v[0] - 1, v[1])
        };
    }
}

/*
python misc/run.py atcoder/abc288/d/main.rs

%%%% begin
7 3
3 -1 1 -2 2 0 5
2
1 6
2 7
%%%%
Yes
No
%%%% end

%%%% begin
20 4
-19 -66 -99 16 18 33 32 28 26 11 12 0 -16 4 21 21 37 17 55 -19
5
13 16
4 11
3 12
13 18
4 10
%%%%
No
Yes
No
Yes
No
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
