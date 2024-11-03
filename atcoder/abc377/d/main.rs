// AC

// https://atcoder.jp/contests/abc377/tasks/abc377_d

fn main() {
    // ~ 10^5
    let [n, m]: [usize; 2] = read_array();
    let pairs: Vec<[usize; 2]> = (0..n).map(|_| read_array()).collect();

    // count negated condition:
    //   (l, r) s.t. ∃x. l ≤ Lx and Rx ≤ r

    let mut lrs: Multiset<[usize; 2]> = Multiset::new();
    let mut rs: Multiset<usize> = Multiset::new();
    for &p in &pairs {
        lrs.insert(p);
        rs.insert(p[1]);
    }

    let mut count = 0;
    for l in 1..=m {
        // remove Lx < l
        loop {
            if let Some(lr) = lrs.first() {
                if lr[0] < l {
                    rs.remove(&lr[1]);
                    lrs.pop_first();
                    continue;
                }
            }
            break;
        }

        // find minimum Rx
        if let Some(r) = rs.first() {
            count += m - r + 1;
        }
    }

    println!("{}", (m + 1) * m / 2 - count);
}

/*
python misc/run.py atcoder/abc377/d/main.rs

%%%% begin
2 4
1 2
3 4
%%%%
5
%%%% end

%%%% begin
6 5
1 1
2 2
3 3
4 4
5 5
1 5
%%%%
0
%%%% end

%%%% begin
6 20
8 12
14 20
11 13
5 19
4 11
1 6
%%%%
102
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

    fn insert(&mut self, k: K) {
        *self.map.entry(k).or_default() += 1;
    }

    fn remove(&mut self, k: &K) {
        if let Some(v) = self.map.get_mut(k) {
            assert!(*v > 0);
            if *v > 1 {
                *v -= 1;
            } else {
                self.map.remove(&k);
            }
        }
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
