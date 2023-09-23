// WIP

// https://atcoder.jp/contests/abc297/tasks/abc297_e

use std::collections::BTreeSet;

fn main() {
    // n ~ 10
    // k ~ 10^5
    let (_n, k) = {
        let v: Vec<usize> = read_tokens();
        (v[0], v[1])
    };

    // ~ 10^9
    let ls: Vec<usize> = read_tokens();

    // PROP.
    //   answer <= min(ls) x k <= 10^14

    let mut queue: BTreeSet<usize> = BTreeSet::new();
    queue.insert(0);
    for _ in 0..k {
        let x = pop_first(&mut queue).unwrap();
        for &a in &ls {
            queue.insert(x + a);
        }
    }
    let result = pop_first(&mut queue).unwrap();
    println!("{}", result);
}

// old rust compat
fn pop_first<T: std::cmp::Ord + Copy>(queue: &mut BTreeSet<T>) -> Option<T> {
    if let Some(&e) = queue.iter().next() {
        queue.remove(&e);
        Some(e)
    } else {
        None
    }
}

/*
python misc/run.py atcoder/abc297/e/main.rs

%%%% begin
4 6
20 25 30 100
%%%%
50
%%%% end

%%%% begin
2 10
2 1
%%%%
10
%%%% end

%%%% begin
10 200000
955277671 764071525 871653439 819642859 703677532 515827892 127889502 881462887 330802980 503797872
%%%%
5705443819
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
