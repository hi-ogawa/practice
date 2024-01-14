// AC

// https://atcoder.jp/contests/abc325/tasks/abc325_d

use std::collections::BTreeMap;

fn main() {
    // n ~ 10^5
    // t, d ~ 10^18
    let n: usize = read_vec()[0];

    let mut groups: BTreeMap<usize, Vec<usize>> = BTreeMap::new();
    for _ in 0..n {
        let [t, d]: [usize; 2] = read_array();
        groups.entry(t).or_default().push(t + d);
    }

    // greedily pick first one to expire
    let mut t = 0;
    let mut result = 0;
    let mut remainings = Multiset::new();

    loop {
        if let Some(group) = groups.get(&t) {
            for &v in group {
                remainings.insert(v);
            }
            groups.remove(&t);
        }

        // clear expired ones
        while let Some(&f) = remainings.first() {
            if f >= t {
                break;
            }
            remainings.pop_first();
        }

        // pick first one
        if let Some(_) = remainings.first() {
            t += 1;
            result += 1;
            remainings.pop_first();
            continue;
        }

        // if nothing, fast-forward to next group
        if let Some((&next, _)) = groups.first_key_value() {
            t = next;
            continue;
        }
        break;
    }

    println!("{}", result);
}

// TODO: generalize?
#[derive(Debug)]
struct Multiset {
    map: BTreeMap<usize, usize>,
}

impl Multiset {
    fn new() -> Self {
        Self {
            map: BTreeMap::new(),
        }
    }

    fn insert(&mut self, v: usize) {
        *self.map.entry(v).or_default() += 1;
    }

    fn first(&mut self) -> Option<&usize> {
        self.map.first_key_value().map(|kv| kv.0)
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
}

/*
python misc/run.py atcoder/abc325/d/main.rs

%%%% begin
5
1 1
1 1
2 1
1 2
1 4
%%%%
4
%%%% end

%%%% begin
2
1 1
1000000000000000000 1000000000000000000
%%%%
2
%%%% end

%%%% begin
10
4 1
1 2
1 4
3 2
5 1
5 1
4 1
2 1
4 1
2 4
%%%%
6
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
