// AC

// https://atcoder.jp/contests/abc376/tasks/abc376_e

fn main() {
    let t: usize = read_vec()[0];
    for _ in 0..t {
        solve()
    }
}

fn solve() {
    // n, k ~ 10^5
    // a, b ~ 10^6
    let [n, k]: [usize; 2] = read_array();
    let ls1: Vec<usize> = read_vec();
    let ls2: Vec<usize> = read_vec();

    let mut ls: Vec<(usize, usize)> = ls1.into_iter().zip(ls2.into_iter()).collect();
    ls.sort_by_key(|&(a, _b)| a);

    let mut b_set: Multiset<usize> = Multiset::new();
    let mut b_acc: usize = 0;
    for &(_, b) in &ls[..k] {
        b_set.insert(b);
        b_acc += b;
    }

    let mut result = ls[k - 1].0 * b_acc;

    for &(a, b) in &ls[k..n] {
        let &b_max = b_set.last().unwrap();
        if b < b_max {
            b_set.pop_last();
            b_set.insert(b);
            b_acc = b_acc + b - b_max;
        }
        result = result.min(a * b_acc);
    }

    println!("{}", result);
}

/*
python misc/run.py atcoder/abc376/e/main_v3.rs

%%%% begin
3
3 2
3 7 6
9 2 4
5 3
6 4 1 5 9
8 6 5 1 7
10 6
61 95 61 57 69 49 46 47 14 43
39 79 48 92 90 76 30 16 30 94
%%%%
42
60
14579
%%%% end
*/

#[derive(Debug)]
struct Multiset<K> {
    map: std::collections::BTreeMap<K, usize>,
}

#[allow(dead_code)]
impl<K: Ord> Multiset<K> {
    fn new() -> Self {
        Self {
            map: std::collections::BTreeMap::new(),
        }
    }

    fn insert(&mut self, v: K) {
        *self.map.entry(v).or_default() += 1;
    }

    fn first(&mut self) -> Option<&K> {
        self.map.first_key_value().map(|kv| kv.0)
    }

    fn last(&mut self) -> Option<&K> {
        self.map.last_key_value().map(|kv| kv.0)
    }

    fn pop_first(&mut self) {
        if let Some(mut entry) = self.map.first_entry() {
            let v = entry.get_mut();
            assert!(*v > 0);
            if *v > 1 {
                *v -= 1;
            } else {
                entry.remove();
            }
        }
    }

    fn pop_last(&mut self) {
        if let Some(mut entry) = self.map.last_entry() {
            let v = entry.get_mut();
            assert!(*v > 0);
            if *v > 1 {
                *v -= 1;
            } else {
                entry.remove();
            }
        }
    }
}

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
